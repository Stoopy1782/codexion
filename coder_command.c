/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 14:48:58 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/03 18:30:32 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	compile(t_coder *coder)
{
	if (is_stopped(coder->set) != 1)
	{
		pthread_mutex_lock(&coder->lock_c);
		coder->last_compile = get_time();
		pthread_mutex_unlock(&coder->lock_c);
		print_m(coder, 2);
		usleep(coder->set->time_to_compile * 1000);
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
		usleep(coder->set->time_to_debug * 1000);
	}
}

void	refactor(t_coder *coder)
{
	if (is_stopped(coder->set) != 1)
	{
		print_m(coder, 4);
		usleep(coder->set->time_to_refactor * 1000);
	}
}

void	burn_out(t_coder *coder)
{
	if (is_stopped(coder->set) != 1)
	{
		print_m(coder, 5);
		pthread_mutex_lock(&coder->lock_c);
		coder->is_burnout = 1;
		pthread_mutex_unlock(&coder->lock_c);
		pthread_mutex_lock(&coder->set->lock_stop);
		coder->set->is_stopped = 1;
		pthread_mutex_unlock(&coder->set->lock_stop);
	}
}
