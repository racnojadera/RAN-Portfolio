Technical Assumptions:
 1. The user will oblige to the specified format based on the project specifications. This includes:
    * First Line inputted will be an integer input (without additional spaces or characters)
    * Possible values of S will only be limited to FCFS, SJF, SRTF, P, RR
    * Inputs in the process per line (A, B, P) will be limited to their specifications (A = integer >= 0; B = integer > 0; P = integer -20 <= P <= 20)
    * User will only input Q if SS = R
 2. User will input P regardless if the value of S is "P" or not
 3. Time is an integer
 4. CPU Utilization will always be an integer + %
 5. Throughput will always have 4 decimal places regardless of trailing zeroes
 6. Average times (waiting, turnaround, response) will always be 2 decimal places regardless of trailing zeroes
 7. The PC can compile .cpp files
 8. The PC can run .exe files from .cpp compiles
 9. The PC is running a Windows Operating System
 10. The PC can support all the #include headers in the .cpp file


Explanation:
Basically, the project stores the processdescriptions in a struct, which is stored in a vector generated based on how many cases there are (1 vector of processdescriptions per case).
There is also a vector of strings (treated as an ArrayList) which will contain the instructions per time instance, which will be then called after doing all the cases.



Instructions on running the project:
 a. Navigate through the folder where the .cpp code is located
 b. On the Address Bar on the middle top of the explorer window, type in cmd.exe. This should make the command line pop out with the directory of the folder.
 c. Type in the command line "g++ -o 183529-GP1 183529-GP1.cpp" (without quotation marks). This should create an .exe file with the filename "183529-GP1".
 d. Type in the command line ".\183529-GP1.exe" (without quotation marks). This should run the code.