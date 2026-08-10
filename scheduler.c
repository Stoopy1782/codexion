/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/10 18:50:11 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	request_dongle(t_coder *coder, t_dongle *dongle)
{
	if (!dongle->first_coder)
		dongle->first_coder = coder;
	else if (dongle->first_coder != coder)
		dongle->second_coder = coder;
}

t_coder	*pick_first(t_coder *coder, t_dongle *dongle)
{
	if (!dongle->second_coder)
		return (dongle->first_coder);
	if (coder->set->scheduler == 0)
		return (dongle->first_coder);
	if (dongle->first_coder->last_compile
		< dongle->second_coder->last_compile)
		return (dongle->first_coder);
	else
		return (dongle->second_coder);
}

int	order_dongles(t_coder *coder, t_dongle *dongle)
{
	struct timespec	ts;

	pthread_mutex_lock(&dongle->lock_sch);
	while (dongle->available_time > get_time())
	{
		if (is_stopped(coder->set))
		{
			pthread_mutex_unlock(&dongle->lock_sch);
			return (1);
		}
		ts = get_abstime(dongle->available_time);
		if (pthread_cond_timedwait(&dongle->lock_start,
				&dongle->lock_sch, &ts) != 0)
			break ;
	}
	request_dongle(coder, dongle);
	if (coder == pick_first(coder, dongle))
	{
		pthread_mutex_unlock(&dongle->lock_sch);
		pthread_mutex_lock(&dongle->lock_d);
		print_m(coder, 1);
		return (0);
	}
	pthread_mutex_unlock(&dongle->lock_sch);
	return (1);
}

void	take_dongles(t_coder *coder, t_dongle *dongles)
{
	int	first_dongle;
	int	second_dongle;

	first_dongle = coder->id - 1;
	second_dongle = coder->id;
	if (coder->id == coder->set->number_of_coders)
		second_dongle = 0;
	if (first_dongle > second_dongle)
	{
		first_dongle = second_dongle;
		second_dongle = coder->id - 1;
	}
	if (order_dongles(coder, &dongles[first_dongle]) == 0)
	{
		if (order_dongles(coder, &dongles[second_dongle]) != 0)
		{
			pthread_mutex_unlock(&dongles[first_dongle].lock_d);
		}
	}
}
