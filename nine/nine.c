#include "crypt_lib.c"

int encrypt(char *filename);
int decrypt(char *filename);
char *concat(const char *dest, const char *src);

int main(void) {
	HANDLE fileHandle;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER szDir;
	WIN32_FIND_DATA fileData;
	const char *dir_path;
	const char *vanilla_path = "C:\\Users\\dtf82\\OneDrive\\Documents\\school\\tools\\starter_code\\learning\\nine\\*.txt";

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
		/* DETERMINE HERE IF ENCRYPTING OR DECRYPTING
		encrypt(path);	
		decrypt(path);
		*/
		decrypt(path);
	} while (FindNextFile(fileHandle, &ffd) != 0);
	return 0;
}
