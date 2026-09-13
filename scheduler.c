/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/09/12 17:15:00 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	update_queue(t_coder *coder, t_dongle *dongle, int action)
{
	if (action == 0)
	{
		if (!dongle->first_coder)
			dongle->first_coder = coder;
		else if (dongle->first_coder != coder && !dongle->second_coder)
			dongle->second_coder = coder;
	}
	else
	{
		if (dongle->first_coder == coder)
		{
			dongle->first_coder = dongle->second_coder;
			dongle->second_coder = NULL;
		}
		else if (dongle->second_coder == coder)
			dongle->second_coder = NULL;
	}
}

static t_coder	*pick_first(t_dongle *dongle)
{
	long	d1;
	long	d2;

	if (!dongle->second_coder)
		return (dongle->first_coder);
	if (dongle->set->scheduler == 0)
		return (dongle->first_coder);
	pthread_mutex_lock(&dongle->first_coder->lock_c);
	d1 = dongle->first_coder->last_compile + dongle->set->time_to_burnout;
	pthread_mutex_unlock(&dongle->first_coder->lock_c);
	pthread_mutex_lock(&dongle->second_coder->lock_c);
	d2 = dongle->second_coder->last_compile + dongle->set->time_to_burnout;
	pthread_mutex_unlock(&dongle->second_coder->lock_c);
	if (d1 <= d2)
		return (dongle->first_coder);
	return (dongle->second_coder);
}

static int	wait_or_take(t_coder *coder, t_dongle *dongle)
{
	struct timespec	ts;

	if (!dongle->in_use && get_time() >= dongle->available_time
		&& coder == pick_first(dongle))
	{
		dongle->in_use = 1;
		update_queue(coder, dongle, 1);
		pthread_mutex_unlock(&dongle->lock_sch);
		print_m(coder, 1);
		return (0);
	}
	if (dongle->available_time > get_time())
	{
		ts = get_abstime(dongle->available_time);
		pthread_cond_timedwait(&dongle->lock_start, &dongle->lock_sch, &ts);
	}
	else
		pthread_cond_wait(&dongle->lock_start, &dongle->lock_sch);
	return (-1);
}

int	acquire_dongle(t_coder *coder, t_dongle *dongle)
{
	int	res;

	pthread_mutex_lock(&dongle->lock_sch);
	update_queue(coder, dongle, 0);
	while (!is_stopped(coder->set))
	{
		res = wait_or_take(coder, dongle);
		if (res == 0)
			return (0);
	}
	update_queue(coder, dongle, 1);
	pthread_mutex_unlock(&dongle->lock_sch);
	return (1);
}

void	release_one_dongle(t_coder *coder, t_dongle *dongle, int is_used)
{
	pthread_mutex_lock(&dongle->lock_sch);
	dongle->in_use = 0;
	if (is_used)
		dongle->available_time = get_time() + coder->set->dongle_cooldown;
	pthread_cond_broadcast(&dongle->lock_start);
	pthread_mutex_unlock(&dongle->lock_sch);
}
