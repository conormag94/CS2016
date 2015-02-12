#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef enum { FALSE, TRUE } boolean;

#define checkResults(string, val) {             \
if (val) {                                     \
printf("Failed with %d at %s", val, string); \
exit(1);                                     \
}                                              \
}

#define					BUFFER_CAPACITY 8
#define                 NUMTHREADS      2
pthread_mutex_t         dataMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t          dataPresentCondition = PTHREAD_COND_INITIALIZER;
int                     dataPresent=0;
int                     sharedData=0;

struct buffer{
	int current_items;
	boolean is_full;
}buffer;

void *theProducer(void *threadid){
	return NULL;
}

void *theConsumer(void *threadid){
	return NULL;
}



int main(){

	buffer.current_items = 5;
	buffer.is_full = TRUE;

	printf("%d\n", buffer.current_items);
	printf("%d\n", buffer.is_full);

    return 0;
}
