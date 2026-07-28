#include <pthread.h>
#include <stdlib.h>		/* lrand48(), srand48() */
#include <time.h>		/* time(), nanosleep(), struct timespec */
#include <sys/types.h>
#include <stdio.h>		/* printf() */
#include <stdint.h>		/* intptr_t */

/* プロトタイプ宣言 */
void *func1(void *arg);
void *func2(void *arg);
void sleep_rand(void);

int main(void)
{
	pthread_t t1;
	pthread_t t2;

	srand48(time(NULL));

	/* int型の値をポインタとして渡すためのキャスト (intptr_tを使用) */
	pthread_create(&t1, NULL, func1, (void *)(intptr_t)10);
	pthread_create(&t2, NULL, func2, (void *)(intptr_t)20);

	printf("main()\n");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}

void *func1(void *arg)
{
	/* 渡されたポインタを元のint型に戻す */
	int x = (intptr_t)arg;
	int i;

	for (i = 0; i < 3; i++)
	{
		sleep_rand();
		printf("func1( %d ): %d \n", x, i);
	}
	
	return NULL;
}

void *func2(void *arg)
{
	int x = (intptr_t)arg;
	int i;

	for (i = 0; i < 3; i++)
	{
		sleep_rand();
		printf("func2( %d ): %d \n", x, i);
	}
	
	return NULL;
}

void sleep_rand(void)
{
	long rnd;
	struct timespec req;

	rnd = lrand48();
	req.tv_sec = 0;
	req.tv_nsec = rnd;
	
	nanosleep(&req, NULL);
}
