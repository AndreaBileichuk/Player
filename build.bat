@echo off
echo Compiling Music Player...

gcc src/*.c -o player.exe -I./include -lraylib -lgdi32 -lwinmm

echo Done!
pause