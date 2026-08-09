/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/09 20:33:17 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	request_dongle(t_coder *coder, t_dongle	*dongle)
{
	pthread_mutex_lock(&dongle->lock_sch);
	if (!dongle->first_coder)
		dongle->first_coder = coder;
	else
		dongle->second_coder = coder;
	pthread_mutex_unlock(&dongle->lock_sch);
}

t_coder	*pick_first(t_coder	*coder, t_dongle	*dongle)
{
	pthread_mutex_lock(&dongle->lock_sch);
	if (!dongle->second_coder)
	{
		pthread_mutex_unlock(&dongle->lock_sch);
		return (dongle->first_coder);
	}
	if (coder->set->scheduler == 0)
	{
		pthread_mutex_unlock(&dongle->lock_sch);
		return (dongle->first_coder);
	}
	if (dongle->first_coder->last_compile
		> dongle->second_coder->last_compile)
	{
		pthread_mutex_unlock(&dongle->lock_sch);
		return (dongle->first_coder);
	}
	else
	{
		pthread_mutex_unlock(&dongle->lock_sch);
		return (dongle->second_coder);
	}
}

int	order_dongles(t_coder *coder, t_dongle *dongle)
{
	request_dongle(coder, dongle);
	if (coder == pick_first(coder, dongle))
	{
		pthread_mutex_lock(&dongle->lock_d);
		print_m(coder, 1);
		return (0);
	}
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
	if (first_dongle < second_dongle)
	{
		if (order_dongles(coder, &dongles[first_dongle]) == 0)
			order_dongles(coder, &dongles[second_dongle]);
	}
	else
	{
		if (order_dongles(coder, &dongles[second_dongle]) == 0)
			order_dongles(coder, &dongles[first_dongle]);
	}
}
