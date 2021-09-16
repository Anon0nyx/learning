#include <stdio.h>

/* 
	The purpose of this program is to open the encryptme.txt file
	and to encrypt that file with the results being stored in 
	encrypted.txt. Once the file data is encrypted the program
	unencrypts the data within encrypted.txt and puts this data
	into the decrypted.txt file
*/
int main(void) {
	FILE *file_ptr, *temp_file_ptr;
	char *filename = "encryptme.txt";
	char *tempfile = "temp.txt";
	char *encrypted_file = "encrypted.txt";
	char ch;	
	
	// Open file to read 
	file_ptr = fopen(filename, "r");
	if (file_ptr == NULL)
		return 1;

	// Open temp file to write encrypted char, char by char
	temp_file_ptr = fopen(tempfile, "w");
	if (temp_file_ptr == NULL)
		return 1;

	// Get first character from file
	ch = fgetc(file_ptr);
	// While the file is not ended, add 100 to each character
	// and put these new characters in the temp file
	while (ch != EOF) {
		ch = ch + 100;
		fputc(ch, temp_file_ptr);
		ch = fgetc(file_ptr);
	}
	// Close up these files, our next step is to take the temp file
	// and copy it to the original file
	fclose(file_ptr);
	fclose(temp_file_ptr);

	// Start by opening the encrypted file as write only
	file_ptr = fopen(encrypted_file, "w");
	if (file_ptr == NULL)
		return 1;

	// Open the tempfile as read only
	temp_file_ptr = fopen(tempfile, "r");
	if (temp_file_ptr == NULL)
		return 1;
	// Gather the first character within the temp file
	// Continue to collect these characters as long as we
	// do not reach the EOF character at the end of the file
	ch = fgetc(temp_file_ptr);
	while (ch != EOF) {
		ch = fputc(ch, file_ptr);
		ch = fgetc(temp_file_ptr);
	}
	// Close up the files to finalize the encryption
	fclose(file_ptr);
	fclose(temp_file_ptr);
	printf("File encrypted successfully\n");

	// Begin the decryption by opening the decryption file	
	file_ptr = fopen("decrypted.txt", "w");
	if (file_ptr == NULL)
		return 1;
	// Open the temp file containing the encrypted data
	temp_file_ptr = fopen(encrypted_file, "r");
	if (temp_file_ptr == NULL)
		return 1;

	// Decrypt the data by subtracting 100 from each character
	ch = fgetc(temp_file_ptr);
	while (ch != EOF) {
		ch = ch - 100;
		fputc(ch, file_ptr);
		ch = fgetc(temp_file_ptr);
	}
	// Finalize the decryption by closing all used files
	fclose(file_ptr);
	fclose(temp_file_ptr);
	printf("File decrypted successfully\n");
	
	return 0;
}
