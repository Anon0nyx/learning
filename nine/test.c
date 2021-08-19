#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#define BUFSIZE 4096
#define DIR_NAM TEXT("C:\\Users\\dtf82\\OneDrive\\Documents\\school\\tools\\starter_code\\learning\\nine\\test_files\\")

void main() {
	DWORD retval=0;
	TCHAR buffer[BUFSIZE] = TEXT("");
	TCHAR **lppPart={NULL};

	retval = GetFullPathName("first.txt", BUFSIZE, buffer, lppPart);

	printf("The full path is: %s\n", buffer);
	if (lppPart != NULL && *lppPart != 0) {
		printf("The final component to the path is %s\n", *lppPart);
	}
}
