#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define S_IRWXU 0000700

int main (void) {
	int filedescriptor;
	filedescriptor = open("testfile.txt", O_WRONLY | O_CREAT, S_IRWXU);
	if (filedescriptor < 0) {
		printf("The open operation has failed..");
		return -1;
	} else {
		printf("The file has been created/opened successfully");
		return 0;
	}

	return 0; 
}
