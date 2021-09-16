#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define PERMISSION 0000700

int main(void) {
	int filedescriptor;
	filedescriptor = open("testfile.txt", O_WRONLY | O_CREAT, PERMISSION);
	char *string = "Hello, Friend.";
	if (filedescriptor < 0) {
		printf("The operation has failed\n");
		return -1;
	} else {
		printf("The operation has succeeded\n");
	}	
	int writertn = write(filedescriptor, string, strlen(string));
	if (writertn != strlen(string)) {
		printf("The write operation has failed\n");
		return -1;
	} else {
		printf("The write operation has succeeded!\n");
	}
	return 0;
}
