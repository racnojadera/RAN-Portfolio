#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

int main(void)
{
	pthread_t thread1, thread2;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int  iret1, iret2;

	/* Create independent threads each of which will execute function */

	iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
	iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
    /*
    creates and starts the thread
    returns 0 if successful, otherwise, returns an error code

    1st argument: pointer to a pthread_t
    2nd argument: pointer to a struct pthread_attr_t, which is usually not needed thus we put NULL
    3rd argument: pointer to the thread's run( ) function
        function must contain only 1 argument that is of type void*
        function must also be of type void*
    4th argument: pointer to the function's argument and needs to be of type void*
    */
	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL); 
    /*    
    1st argument: the pthread_t that you are waiting to finish execution
    2nd argument: pointer to what will contain the function's 'exit-return' value which is
        used if pthread_exit( ) is called by the thread
        put NULL instead if you don't need it, which is most of the time
    returns 0 if successful
    */ 

	printf("Thread 1 returns: %d\n",iret1);
	printf("Thread 2 returns: %d\n",iret2);
	return 0;
}

void *print_message_function( void *ptr )
{
	char *message;
	message = (char *) ptr;
	printf("%s \n", message);
}