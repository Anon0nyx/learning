#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define BUFSIZE 4096
#define DIR_PATH TEXT("C:/Users/dtf82/OneDrive/Documents/school/tools/starter_code/learning/nine/test_files")


int encrypt(char *filename);
char *concat(const char *dest, const char *src);

int main(void) {
	HANDLE fileHandle;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER szDir;
	WIN32_FIND_DATA fileData;
	const char *dir_path;
	const char *vanilla_path = "C:\\Users\\dtf82\\OneDrive\\Documents\\school\\tools\\starter_code\\learning\\nine\\test_files\\*.txt";

	DWORD retval = 0;
	BOOL success;
	TCHAR path[BUFSIZE] = TEXT("");
	TCHAR buf[BUFSIZE] = TEXT("");
	TCHAR **lppPart={NULL};
	
	fileHandle = FindFirstFile(vanilla_path, &ffd);
	if (INVALID_HANDLE_VALUE == fileHandle)
		printf("Invalid File Handle Value\n");
	do {
		retval = GetFullPathNameA(ffd.cFileName, BUFSIZE, path, lppPart);
			
		encrypt(path);
	} while (FindNextFile(fileHandle, &ffd) != 0);
	return 0;
}

int encrypt(char *filename) {
	FILE *file_ptr, *temp_file_ptr;
	char *tempfile = "temp.txt";
	char ch;	

	// DEBUGGING HERE
	printf("%s\n", filename);

	// Open file to read 
	file_ptr = fopen((char *)filename, "r");
	if (file_ptr == NULL)
		return 1;
	printf("made it here");
	// Open temp file to write encrypted char, char by char
	temp_file_ptr = fopen(tempfile, "w");
	if (temp_file_ptr == NULL)
		return 1;
	printf("Made it here");
	// Get first character from file
	ch = fgetc(file_ptr);
	printf("%c", ch);
	// While the file is not ended, add 100 to each character
	// and put these new characters in the temp file
	while (ch != EOF) {
		printf("%c", ch);
		ch = ch + 100;
		printf("%c", ch);
		fputc(ch, temp_file_ptr);
		ch = fgetc(file_ptr);
	}
	printf("\n");
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
