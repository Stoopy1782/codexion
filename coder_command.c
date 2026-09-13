/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 14:48:58 by ykojima           #+#    #+#             */
/*   Updated: 2026/09/13 13:48:02 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	short_sleep(long time_ms, t_set *set)
{
	long	start;

	start = get_time();
	while (!is_stopped(set))
	{
		if (get_time() - start >= time_ms)
			break ;
		usleep(500);
	}
}

void	compile(t_coder *coder)
{
	if (is_stopped(coder->set) != 1)
	{
		pthread_mutex_lock(&coder->lock_c);
		coder->last_compile = get_time();
		pthread_mutex_unlock(&coder->lock_c);
		print_m(coder, 2);
		short_sleep(coder->set->time_to_compile, coder->set);
		pthread_mutex_lock(&coder->lock_c);
		coder->compile_count += 1;
		pthread_mutex_unlock(&coder->lock_c);
	}
}

void	debug(t_coder *coder)
{
	if (is_stopped(coder->set) != 1)
	{
		print_m(coder, 3);
		short_sleep(coder->set->time_to_debug, coder->set);
	}
}

void	refactor(t_coder *coder)
{
	if (is_stopped(coder->set) != 1)
	{
		print_m(coder, 4);
		short_sleep(coder->set->time_to_refactor, coder->set);
	}
}
