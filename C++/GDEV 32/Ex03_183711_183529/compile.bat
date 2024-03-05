@echo off
set include_folder="D:\Raymond Nojadera\Coding\GDEV-32 Final\Include"
set libraries_folder="D:\Raymond Nojadera\Coding\GDEV-32 Final\Libraries"

@echo on
g++ *.cpp glad.c -o out -I %include_folder% -L %libraries_folder% -lglfw3dll -lopengl32 -mwindows
pause