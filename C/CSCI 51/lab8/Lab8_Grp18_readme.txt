Lab 8 - CIPC (Local) 
Two C/C++ programs (producer and consumer) that uses semaphores and shared memory in order to communicate 
with each other. When combined, these two programs will simply be an inter-process version of the 
cp (copy) command.

Usage:
Compile and run the program by running these commands in your terminal:

// PRODUCER CODE:
// This generates the executable file
gcc -o producer ./Lab8_Grp18_procedure_code.c

// CONSUMER CODE:
// This generates the executable file
gcc -o consumer ./Lab8_Grp18_consumer_code.c

// To run the file
// PRODUCER CODE:
./producer test.txt 5
// CONSUMER CODE:
./consumer testCopy.txt 5