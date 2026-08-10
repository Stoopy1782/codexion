/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 17:21:26 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/10 15:59:47 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

struct timespec	get_abstime(long available_time)
{
	struct timespec	ts;

	ts.tv_sec = available_time / 1000;
	ts.tv_nsec = (available_time % 1000) * 1000000;
	return (ts);
}
