#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "cryptLib.c"
#include "queue.c"

#define EXPECTED_PATH "./first_layer"

void copy_string(char *target, char *source);

void copy_string(char *target, char *source) {
	while (*source) {
		*target = *source;
		source++;
		target++;
	}
	*target = '\0'; // Once at the end of the source string create a termination character for our new string location
}

int breadthFirstDirSearch(queue *dirQueue, char *path) {
	struct dirent *dir_entry;
	DIR *dr = opendir(path);
	int count = 0;
	char currentPath[3] = "/";
	unsigned char key = 4;
	char *new_path;
	strcat(path, currentPath);
	if (dr == NULL) {
		printf("Could not open directory: %s\n", path);
		return 1;
	}
	while ((dir_entry = readdir(dr)) != NULL) {
		printf("Opened directory/file: %s\n", dir_entry->d_name);
		if (!(strcmp((char *)dir_entry->d_name, ".") == 0 || strcmp((char *)dir_entry->d_name, "..") == 0)) {
			if (dir_entry->d_type == key) {
				char dest[100];
				strcpy(dest, path);
				strcat(dest, dir_entry->d_name);
				queueAdd(dirQueue, dest);	
				count++;
			} else if (dir_entry->d_type == 8) {
				char dest[100];
				strcpy(dest, path);
				strcat(dest, dir_entry->d_name);
			}
		}
	}
	if (count == 0) return 1;
	queueRemove(dirQueue);
	new_path = dirQueue->first->dr;
	breadthFirstDirSearch(dirQueue, new_path);
	return 0;
}

int main() {
	char path[256];
	const char *test_path = "/";
	getcwd(path, sizeof(path));
	queue directories;
	queueInitialize(&directories);

	if (strcmp(EXPECTED_PATH, path) == 0) {
		breadthFirstDirSearch(&directories, path);
	} else {
		chdir(EXPECTED_PATH);
		getcwd(path, sizeof(path));
	}

	breadthFirstDirSearch(&directories, path);

	return 0;
}
