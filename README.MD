*This project has been created as part of the 42 curriculum by ykojima*

# Codexion

## Description 

## Coder's Flow
```
Take 2 USB dongles
(Can't take 2 dongles at tha same time)
↓
Compile
↓
(Return 2 USB dongles)
↓
Debug
↓
Refactor
↓
Burn out

```
## Argument Description 
This program run with 8 arguments.
```
./a.out <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

```
◦ number_of_coders: The number of coders and also the number of dongles.
◦ time_to_burnout (in milliseconds): If a coder did not start compiling within
time_to_burnout milliseconds since the beginning of their last compile or the
beginning of the simulation, they burn out.
◦ time_to_compile (in milliseconds): The time it takes for a coder to compile.
During that time, they must hold two dongles.
◦ time_to_debug (in milliseconds): The time a coder will spend debugging.
◦ time_to_refactor (in milliseconds): The time a coder will spend refactoring.
After completing the refactoring phase, the coder will immediately attempt to
acquire dongles and start compiling again.
◦ number_of_compiles_required: If all coders have compiled at least this
many times, the simulation stops. Otherwise, it stops when a coder burns
out.
◦ dongle_cooldown (in milliseconds): After being released, a dongle is unavail-
able until its cooldown has passed.
◦ scheduler: The arbitration policy used by dongles to decide who gets them
when multiple coders request them.
The value must be exactly one of: fifo or edf.
fifo means First In, First Out: the dongle is granted to the coder whose
request arrived first.
edf means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
```


## External Functions
```
<pthread.h>
pthread_create, pthread_join, pthread_mutex_init,
pthread_mutex_lock,
pthread_mutex_unlock, pthread_mutex_destroy,
pthread_cond_init,
pthread_cond_wait, pthread_cond_timedwait,
pthread_cond_signal,
pthread_cond_broadcast, pthread_cond_destroy

<stdio.h>
printf, fprintf

<stdlib.h>
atoi, malloc, free

<string.h>
strcmp, memset

<sys/time.h>
gettimeofday

<time.h>
clock_gettime

<unistd.h>
usleep, write, strlen
```

## Resources
-時間情報の取得方法と扱い方
https://www.mm2d.net/main/prog/c/time-01.html

-[C言語]マルチスレッドを触ってみる
https://zenn.dev/rinngo0302/articles/d1aa031137de9f


