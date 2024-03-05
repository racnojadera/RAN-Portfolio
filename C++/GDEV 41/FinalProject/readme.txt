How to compile:

* Run w64devkit.exe and change directory to extracted .zip folder location

* copy and paste the follwing command to the line:

g++ Main.cpp -o out -I raylib/ -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm


*The directory should now have a file named 'out.exe'. Open this file and the game/application should run.