#include "utils.h"

void	take_dongles(t_coder *coder, t_dongle *dongles)
{
	int	first_dongle;
	int	second_dongle;
	long now;

	first_dongle = coder->id-1;
	second_dongle = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second_dongle = 0;
	if (first_dongle < second_dongle)
	{
		pthread_mutex_lock(&dongles[first_dongle].lock_d);
		now = get_time();
		printf("%ld %d has taken a dongle\n", (now - coder->set->start_time), coder->id);
		pthread_mutex_lock(&dongles[second_dongle].lock_d);
		now = get_time();
		printf("%ld %d has taken a dongle\n", (now - coder->set->start_time), coder->id);
	}
	else
	{
		pthread_mutex_lock(&dongles[second_dongle].lock_d);
		now = get_time();
		printf("%ld %d has taken a dongle\n", (now - coder->set->start_time), coder->id);
		pthread_mutex_lock(&dongles[first_dongle].lock_d);
		now = get_time();
		printf("%ld %d has taken a dongle\n", (now - coder->set->start_time), coder->id);
	}
}

void	release_dongles(t_coder *coder, t_dongle *dongles)
{
	int		first_dongle;
	int		second_dongle;
	long	now;

	first_dongle = coder->id - 1;
	second_dongle = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second_dongle = 0;

	now = get_time();

	// 解放する瞬間に「次に使える時刻」を計算してセットしておく
	dongles[first_dongle].available_time = now + coder->set->dongle_cooldown;
	dongles[second_dongle].available_time = now + coder->set->dongle_cooldown;

	// ロック解除
	pthread_mutex_unlock(&dongles[first_dongle].lock_d);
	pthread_mutex_unlock(&dongles[second_dongle].lock_d);
}

void    *coder_routine(void *arg)
{
    t_coder *coder = (t_coder *)arg;

    // t_coder 構造体に dongles へのポインタを持たせて渡す
    take_dongles(coder, coder->dongles);
    release_dongles(coder, coder->dongles);
    return (NULL);
}
/*
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
*/
