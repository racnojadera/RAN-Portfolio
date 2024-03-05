#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Incorrect number of arguments.\n");
        printf("<textfile> & <shared memory size in bytes>\n");
        exit(1);
    }

    int shmId;
    key_t shmKey = 7252;
    int shmSize = 1 << 10;
    int shmFlags = IPC_CREAT | 0666;
    char *sharedMem;
    shmId = shmget( shmKey, shmSize, shmFlags );
    sharedMem = (char *)shmat(shmId, NULL, 0);

    // -- semaore Initialization --

    int semId;
    key_t semKey = 1234;
    int semFlag = IPC_CREAT | 0666;
    int nSems = 1;
    
    // Attempt to get a semaore set
    // Returns -1 if there was an error.
    semId = semget( semKey, nSems, semFlag );
    if (semId == -1)
    {
        perror( "semget" );
        exit(1);
    }

    // -- semaore Accessing --

    // Perform 2 operations
    int nOperations = 2;

    // Create an array of size 2 to hold
    // the operations that we will do on the semaphore set
    struct sembuf sema[nOperations];

    // Definition for the first operation
    // Our first operation will be to wait for the
    // semaphore to become 0
    sema[0].sem_num = 0;
    sema[0].sem_op = 0;
    sema[0].sem_flg = SEM_UNDO;

    sema[1].sem_num = 0;
    sema[1].sem_op = 1;
    sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

    int opResult = semop( semId, sema, nOperations );
    if (opResult != -1)
    {
        printf("Successfully incremented semaore!\n");

        // -- Do stuff --

        char *source = NULL;
        long bufferSize;
        FILE *filePath = fopen(argv[1], "r");
        if (filePath != NULL)
        {
            if (fseek(filePath, 0L, SEEK_END) == 0)
            {
                bufferSize = ftell(filePath);
                if (bufferSize == -1)
                {
                }
                source = malloc(sizeof(char) * (bufferSize + 1));
                if (fseek(filePath, 0L, SEEK_SET) != 0)
                { 
                }
                size_t newLength = fread(source, sizeof(char), bufferSize, filePath);
                if (ferror(filePath) != 0)
                {
                    fputs("Error reading file", stderr);
                }
                else
                {
                    source[newLength++] = '\0';
                }
            }
            fclose(filePath);
        }

        if( ((int *)sharedMem) == (int *)-1 )
        {
            perror("shmop: shmat failed");
        }
        else
        {
            int chunk = atoi(argv[2]);
            long toWrite = bufferSize + 1;
            int pointer = 0;
            while (toWrite > 0)
            {

                long chunkSize;
                if (toWrite > chunk)
                {
                    chunkSize = chunk;
                }
                else
                {
                    chunkSize = toWrite;
                }
                char chunkBuffer[chunkSize];
                memcpy(chunkBuffer, &source[(pointer*chunk)], chunkSize);
                memcpy(&sharedMem[(pointer*chunk)], chunkBuffer, chunkSize);
                toWrite -= chunkSize;
                pointer++;
                printf("written\n");
                usleep(10000);
            }
        }
        free(source);

        int a;
        a = shmdt(sharedMem);
        if (a == -1)
        {
            perror("shmop: shmdt failed");
        }

        // -- Semaphore Releasing --

        // Set number of operations to 1
        nOperations = 1;

        // Modify the first operation such that it
        // now decrements the semaore.
        sema[0].sem_num = 0;
        sema[0].sem_op = -1; // Decrement semaore by 1
        sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

        opResult = semop(semId, sema, nOperations);
        if (opResult == -1)
        {
            perror("semop (decrement)");
        }
        else
        {
            printf("Done!\n");
        }
    }
    else
    {
        perror("semop (increment)");
    }

    return 0;
}