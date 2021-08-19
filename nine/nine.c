#include <stdio.h>
#include <windows.h>

int main(void) {
	HANDLE fileHandle;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER szDir;
	WIN32_FIND_DATA fileData;
	fileHandle = FindFirstFile("C:\\Users\\dtf82\\OneDrive\\Documents\\school\\tools\\starter_code\\learning\\nine\\test_files\\*.txt", &ffd);
	if (INVALID_HANDLE_VALUE == fileHandle)
		printf("Invalid File Handle Value\n");
	do {
		printf("%s\n", ffd.cFileName);
	} while (FindNextFile(fileHandle, &ffd) != 0);
	return 0;
}
