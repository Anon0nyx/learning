#include "crypt_lib.c"

int encrypt_file(char *filename);
int decrypt_file(char *filename);

/*
	The purpose of this program is to either encryt
	or decrypt all .txt files within the given directory.
	If given any command line arguments the program will
	encrypt the files and if given 0 arguments it will
	decrypt the files.
*/
int main(int argc, char *argv[]) {
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
		if (argc > 1)
			encrypt_file(path);
		else
			decrypt_file(path);
	} while (FindNextFile(fileHandle, &ffd) != 0);
	return 0;
}
