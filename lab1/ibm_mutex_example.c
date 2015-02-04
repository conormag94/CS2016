#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define checkResults(string, val) {             \
if (val) {                                     \
printf("Failed with %d at %s", val, string); \
exit(1);                                     \
}                                              \
}

// From http://publib.boulder.ibm.com/infocenter/iseries/v5r3/index.jsp?topic=/rzahw/rzahwe18rx.htm
// Fixed to avoid calls to non-standard pthread_getthreadid_np()

#define                 NUMTHREADS   1000
pthread_mutex_t         mutex = PTHREAD_MUTEX_INITIALIZER;
int                     sharedData=0;
int                     sharedData2=0;

void *theThread(void *threadid)
{
	int   rc;
//	printf("Thread %.8x: Entered\n", (int)threadid);
	//rc = pthread_mutex_lock(&mutex);
	//checkResults("pthread_mutex_lock()\n", rc);
	
	/********** Critical Section *******************/
	// printf("Thread %.8x: Start critical section, holding lock\n",(int)threadid);
	/* Access to shared data goes here */
	int x = sharedData;
	x=x+1;
	// sleep for a [pseudo] random time 0 to 0.5 seconds
	sleep((random()%500000)/1000000.0);
	sharedData = x;
//	printf("Thread %.8x: done incrementing sharedData.\n",(int)threadid);
	++sharedData;
	--sharedData2;
//	 printf("Thread %.8x: End critical section, release lock\n",(int)threadid);
	/********** Critical Section *******************/
	
	//rc = pthread_mutex_unlock(&mutex);
	//checkResults("pthread_mutex_unlock()\n", rc);
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t             thread[NUMTHREADS];
	int                   rc=0;
	int                   i;
	
	printf("Enter Testcase - %s\n", argv[0]);
	
	printf("Hold Mutex to prevent access to shared data\n");
	rc = pthread_mutex_lock(&mutex);
	checkResults("pthread_mutex_lock()\n", rc);
	
	printf("Create/start threads\n");
	for (i=0; i<NUMTHREADS; ++i) {
		rc = pthread_create(&thread[i], NULL, theThread, (void *)i);
		checkResults("pthread_create()\n", rc);
	}
	
	printf("Wait a bit until we are 'done' with the shared data\n");
	sleep(10);
	printf("Unlock shared data\n");
	rc = pthread_mutex_unlock(&mutex);
	checkResults("pthread_mutex_lock()\n",rc);
	
	printf("Wait for the threads to complete, and release their resources\n");
	for (i=0; i <NUMTHREADS; ++i) {
		rc = pthread_join(thread[i], NULL);
		checkResults("pthread_join()\n", rc);
	}
	
	printf("Results: sharedData: %d, sharedData2: %d\n",sharedData,sharedData2);
	
	printf("Clean up\n");
	rc = pthread_mutex_destroy(&mutex);
	printf("Main completed\n");
	return 0;
}
