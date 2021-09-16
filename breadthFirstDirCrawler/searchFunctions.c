#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "cryptLib.c"

int breadthFirstDirSearch(queue *dirQueue, char *path) {
	struct dirent *dir_entry;
	DIR *dr = opendir(path);
	int count = 0;
	char currentPath[3] = "./";
	unsigned char key = 4;
	char *new_path;

	strcat(path, currentPath);
	printf("%s\n", path);
	if (dr == NULL) {
		printf("Could not open directory: %s\n", path);
		return 1;
	}
	while ((dir_entry == readdir(dr)) != NULL) {
		if (!(strcmp((char *)dir_entry->d_name, ".") == 0 || strcmp((char *)dir_entry->d_name, "..") == 0)) {
			if (dir_entry->d_type == key) {
				char dest[100];
				strcpy(dest, path);
				strcat(dest, dir_entry->d_name);
				printf("%s\n", dest);
				enqueue(&dirQueue, dest);	
				count++;
			} else if (dir_entry->d_type == 8) {
				char dest[100];
				strcpy(dest, path);
				strcat(dest, dir_entry->d_name);
			}
		}
	}
	if (count == 0) return 1;
	new_path = dirQueue->first->next->dr;
	breadthFirstDirSearch(dirQueue, new_path);
	return 0;
}
/*
int depthFirstDirSearch(char *path) {
	struct dirent *dir_entry;
	DIR *dr = opendir(path);
	int count = 0;
	char currentPath[3] = "./";
	unsigned char key = 4;

	strcat(path, currentPath);

	if (dr == NULL) {
		printf("Couldnt open directory: %s\n", path);
		return 1;
	}

	while ((dir_entry = readdir(dr)) != NULL) {
		if (!(strcmp((char *)dir_entry->d_name, ".") == 0 || strcmp((char *)dir_entry->d_name, "..") == 0)) {
			if (dir_entry->d_type == key) {
				char dest[100];
				strcpy(dest, path);
				strcat(dest, dir_entry->d_name);
				printf("%s\n", dest);
				search_directory_tree(dest);
				count++;
			} else if (dir_entry->d_type == 8) {
				char dest[100];
				strcpy(dest, path);
				strcat(dest, dir_entry->d_name);
				decrypt_file(dest);
			}
		}
	}
	if (count == 0) return 1;
	
	closedir(dr);
	return 0;
}
*/

