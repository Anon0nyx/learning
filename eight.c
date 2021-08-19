#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	FILE *file_ptr, *temp_file_ptr, *encrypt_file_ptr;
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
		ch = fgetc(temp_file_ptr);
	}
	// Close up these files, our next step is to take the temp file
	// and copy it to the original file
	fclose(file_ptr);
	fclose(temp_file_ptr);

	file_ptr = fopen(encrypted_file, "w");
	if (file_ptr == NULL)
		return 1;

	temp_file_ptr = fopen(tempfile, "r");
	if (temp_file_ptr == NULL)
		return 1;

	ch = fgetc(temp_file_ptr);
	while (ch != EOF) {
		ch = fputc(ch, file_ptr);
		ch = fgetc(temp_file_ptr);
	}

	fclose(file_ptr);
	fclose(temp_file_ptr);
	printf("File encrypted successfully");
	return 0;
}
