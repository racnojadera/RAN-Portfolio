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
        printf("<textfileCopy> & <shared memory size in bytes>\n");
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
    if( semId == -1 )
    {
        perror("semget");
        exit( 1 );
    }

    // -- Semaphore Accessing --

    // Perform 2 operations
    int nOperations = 2;
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

    int op_result = semop(semId, sema, nOperations);

    // If we successfully incremented the semaphore,
    // we can now do stuff.
    if ( op_result != -1 )
    {
        printf("Reading producer inputs\n");

        if (((int*)sharedMem) == (int*)-1)
        {
            perror("shmop: shmat failed");
        }
        else
        {
            FILE *filePath;
            filePath = fopen(argv[1], "w");

            if (filePath == NULL)
            {
                printf("Error!");
                exit(1);
            }

            size_t length = strlen(sharedMem);
            int chunk = atoi(argv[2]);
            size_t toWrite = length + 1;
            size_t pointer = 0;

            while (toWrite > 0)
            {
                size_t chunkSize;
                if (toWrite > chunk)
                {
                    chunkSize = chunk;
                }
                else
                {
                    chunkSize = toWrite;
                }
                char chunkBuffer[chunkSize];
                memcpy(chunkBuffer, &sharedMem[(pointer * chunk)], chunkSize);
                fprintf(filePath, "%s", chunkBuffer);
                toWrite -= chunkSize;
                pointer++;
                usleep(10000);
            }
            fclose(filePath);
            shmctl(shmId, IPC_RMID, NULL);

            // -- Semaphore Releasing --

            // Set number of operations to 1
            nOperations = 1;

            // Modify the first operation such that it
            // now decrements the semaore.
            sema[0].sem_num = 0;
            sema[0].sem_op = -1; // Decrement semaore by 1
            sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

            op_result = semop(semId, sema, nOperations);
            if (op_result == -1)
            {
                perror("semop (decrement)");
            }
            else
            {

                printf("Successfully read\n");
            }
        }
    }
    else
    {
        perror("semop (increment)");
    }

    return 0;
}