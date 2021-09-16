#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define BUFSIZE 4096

int encrypt_file(char *filename) {
	FILE *file_ptr, *temp_file_ptr;
	char *tempfile = "temp.data";
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
		ch = ch + 50;
		fputc(ch, temp_file_ptr);
		ch = fgetc(file_ptr);
	}
	// Close up these files, our next step is to take the temp file
	// and copy it to the original file
	fclose(file_ptr);
	fclose(temp_file_ptr);

	// Start by opening the encrypted file as write only
	file_ptr = fopen(filename, "w");
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

	return 0;
}

int decrypt_file(char *fileName) {
	FILE *filePtr, *tempFilePtr;
	char *tempFile = "temp.data";
	char ch;
	
	filePtr = fopen(fileName, "r");
	if (filePtr == NULL)
		printf("Failed A");		

	tempFilePtr = fopen(tempFile, "w");
	if (tempFilePtr == NULL)
		printf("Failed B");
	
	ch = fgetc(filePtr);
	while (ch != EOF) {
		ch = (char)ch - 50;
		fputc((char)ch, tempFilePtr);
		ch = fgetc(filePtr);
	}
	fclose(filePtr);
	fclose(tempFilePtr);

	filePtr = fopen(fileName, "w");
	tempFilePtr = fopen(tempFile, "r");

	ch = fgetc(tempFilePtr);
	while (ch != EOF) {
		fputc((char)ch, filePtr);
		ch = fgetc(tempFilePtr);
	}
	fclose(filePtr);
	fclose(tempFilePtr);
	printf("File decrypted successfully\n");

	return 0;
}
