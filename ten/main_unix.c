#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define BUFSIZE 256

void copy_string(char *target, char *source);
int search_directory_tree(char *path);

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
		if (strcmp(dir_entry->d_name, ".") || strcmp(dir_entry->d_name, ".."))
		char dest[100];
		int test, count = 0;
		copy_string(dest, path);
		strcat(dest, dir_entry->d_name);
		printf("%s\n", dest);
		test = chdir(dest);
		printf("%d\n", test);
		count++;
		if (dir_entry->d_type == key) search_directory_tree(dest);
	}
	if (count == 0) return 1;
	

	closedir(dr);
	return 0;
}

void copy_string(char *target, char *source) {
	while (*source) {
		*target = *source;
		source++;
		target++;
	}
	*target = '\0';
}

int main() {
	char path[BUFSIZE];
	const char *test_path = "/";
	getcwd(path, sizeof(path));


	if (strcmp(test_path, path) == 0) {
		//printf("Path correct: %s\n%s\n", path, test_path);
	} else {
		//printf("Path incorrect: %s\nPath needed: %s\nChanging Path\n", path, test_path);
		chdir("./");
		getcwd(path, sizeof(path));
		//printf("New Path: %s\n", path);
	}

	search_directory_tree(path);

	return 0;
}
