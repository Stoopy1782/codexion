#include "sample.h"

int main(void)
{
	int r1= 0;
	int r2 =0;
	int r3 =0;

	pthread_t thread1, thread2;
	pthread_mutex_t r3_mutex;
	pthread_mutex_init(&r3_mutex, NULL);
	pthread_create(&thread1, NULL, (void *)do_one_thing, (void *) &r1);
	pthread_create(&thread2, NULL, (void *)do_another_thing, (void *) &r2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	do_wrap_up(r1, r2);
}
