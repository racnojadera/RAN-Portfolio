#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>

long double get_factorial(double long num){
    double factNum = 1;
    for (int i = 1; i <= num; ++i){
        factNum *= i;
    }
    return factNum;
}

void *get_sin( void *ptr );
long double *sum;
long double xValue;
pthread_t *thread = NULL;
long double finalSum;
int threadTotal;

int main(int argc, char *argv[])
{
    threadTotal = atoi(argv[1]);
    xValue = atof(argv[2]);
    xValue = xValue * (3.14159/180.0);
    thread = malloc(sizeof(pthread_t) * threadTotal);
    sum = malloc(sizeof(long double)* threadTotal);
    for (int i = 0; i < threadTotal; i++)
    {
        pthread_create(&thread[i], NULL, get_sin, (void *)(intptr_t)i);
    }

    for (int j = 0; j < threadTotal; j++)
    {
        pthread_join(thread[j], NULL);
    }
    
    for (int i = 0; i < threadTotal; i++)
    {
        finalSum = finalSum + sum[i];
    }
    printf("Final Sum: %Lf\n",finalSum);
	return 0;
}

void *get_sin( void *ptr )
{
    double x;
    long double out;
	int threadNum = (intptr_t)ptr;
   
    for (int n=threadNum; n<(threadNum+pow(3,5)); n = n+4){
        x = 2*n+1;
        sum[threadNum] = ((pow(-1,n)/get_factorial(x)) * pow(xValue,(2*n+1))) + sum[threadNum];
    }
    printf("Thread %d Sum: %Lf\n", threadNum, sum[threadNum]);
}