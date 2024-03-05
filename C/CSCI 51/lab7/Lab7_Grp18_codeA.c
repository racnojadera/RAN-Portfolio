#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

void *print_arr_numbers(void *ptr);
pthread_t *thread = NULL;
int *arr = NULL;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("error no args passed");
        return 0;
    }

    // pthread_t thread[argc-1];

    // thread[argc - 1];

    thread = malloc(sizeof(pthread_t) * (argc - 1));
    arr = malloc(sizeof(int) * (argc - 1));

    for (int i = 0; i < argc - 1; i++)
    {
        arr[i] = atoi(argv[i + 1]);
        // printf("%d", arr[i]);
    }
    for (int j = 0; j < argc - 1; j++)
    {
        // char *arrNum = (intptr_t)i;
        pthread_create(&thread[j], NULL, print_arr_numbers, (void *)(intptr_t)j);
    }

    for (int k = 0; k < argc - 1; k++)
    {
        pthread_join(thread[k], NULL);
    }

    return 0;
}

void *print_arr_numbers(void *ptr)
{
    int arrNum = (intptr_t)ptr;

    int number = arr[arrNum];
    int numCube = number * number * number;
    int numNegated = number * -1;

    int isEven = arrNum % 2;

    if (isEven == 0)
    {
        /* code */
        printf("arr[%d](%d) has been replaced with arr[%d](%d) \n", arrNum, number, arrNum, numCube);
        arr[arrNum] = numCube;
    }
    else
    {
        printf("arr[%d](%d) has been replaced with arr[%d](%d) \n", arrNum, number, arrNum, numNegated);
        arr[arrNum] = numNegated;
    }
    return 0;
}