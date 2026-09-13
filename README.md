*This project has been created as part of the 42 curriculum by ykojima*

# Codexion

## Description
Codexion is a concurrent programming project inspired by the classic Dining Philosophers Problem, adapted into a modern software developer scenario.

In this simulation, multiple coders (threads) sit in a circle and share USB dongles (shared resources) required to compile their code. The objective is to manage thread synchronization, avoid concurrency pitfalls such as deadlocks, race conditions, and starvation, and implement custom arbitration policies (FIFO and EDF) with resource cooldown periods.

## Instructions
### 1. Clone repository
```
git clone {this program url}
```

### 2. Run program
```
make (all)
```

### 3. Run the simulation
Run the program with the required 8 arguments:
```
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

Example:
```
# 4 coders, burnout 800ms, compile 200ms, debug 200ms, refactor 200ms, 5 compiles, no cooldown, FIFO
./codexion 4 800 200 200 200 5 0 fifo

# 5 coders with 50ms dongle cooldown using EDF scheduler
./codexion 5 800 200 100 100 3 50 edf
```

#### Other options
*   **`make all`**: Build the executable.
*   **`make clean`**: Remove object files.
*   **`make fclean`**: Remove object files and the executable.
*   **`make re`**: Rebuild everything from scratch.

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
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
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

## Blocking cases handled
* **Deadlock Prevention**: Breaks Coffman's *Circular Wait* condition using a **Resource Hierarchy** — coders always acquire dongles in ascending index order (`min` then `max`).
* **Starvation Prevention**: Contested dongles are queued and arbitrated using FIFO or EDF; `pthread_cond_broadcast` ensures waiting coders are not ignored.
* **Cooldown Handling**: Uses `pthread_cond_timedwait` for accurate, non-busy cooldown waits without consuming unnecessary CPU cycles.
* **Precise Burnout Detection**: A dedicated monitor thread checks each coder's `last_compile` every 1ms under mutex protection to catch burnouts promptly.
* **Log Serialization**: All console outputs are synchronized via a global print mutex (`lock_s`), preventing message interleaving and suppressing logs post-burnout.

## Thread synchronization mechanisms

### 1. Primitives & Protected Resources
* **`lock_s` (`pthread_mutex_t`)**: Protects console printing to ensure thread-safe, serialized output.
* **`lock_stop` (`pthread_mutex_t`)**: Protects the global `is_stopped` simulation termination flag.
* **`lock_c` (`pthread_mutex_t`)**: Guards each coder's `last_compile` timestamp and `compile_count`.
* **`lock_sch` (`pthread_mutex_t`)**: Guards each dongle's request queue (`first_coder`, `second_coder`) and `in_use` status.
* **`lock_start` (`pthread_cond_t`)**: Signals waiting coders when a dongle is released or finishes cooldown.

### 2. Coordination & Race Condition Prevention
* **Dongle Coordination**: Coders wait on `lock_start` via `cond_wait` (in-use) or `cond_timedwait` (cooldown). A releasing coder broadcasts to wake contenders, allowing FIFO/EDF to select the rightful successor.
* **Race-Free State Sharing**: Coders write to `last_compile` under `lock_c`, and the monitor reads it under the same mutex, completely preventing data races.
* **Safe Termination**: When the monitor sets `is_stopped = 1`, coder threads detect it through polling in `short_sleep` and cleanly release resources before exiting.

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

-【C言語入門】sleep関数で一定時間停止(Sleep/usleepの違いも解説)
https://www.sejuku.net/blog/48301

-相互排他ロックの使用方法
https://docs.oracle.com/cd/E19504-01/805-0672/6j0mrl70m/index.html

-Pthreads Programming
by Nichols, Buttlar, and Farrell (O'Reilly Media)

## How AI was used
* **Feature Implementation & Bug Fixes**: Assisting with minor routine logic implementations and bug fixes.
* **Norminette Formatting**: Formatting code and aligning declarations to strictly comply with 42 Norminette rules.
* **Code Review & Clean-up**: Reviewing thread synchronization and removing unused code/variables.
* **Documentation**: Drafting technical explanations for this README.
