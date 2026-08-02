/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 14:48:58 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/02 19:50:19 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	compile(t_coder *coder)
{
	if (coder->set->is_stopped != 1)
	{
		pthread_mutex_lock(&coder->set->lock_s);
		coder->last_compile = get_time();
		pthread_mutex_unlock(&coder->set->lock_s);
		print_m(coder, 2);
		usleep(coder->set->time_to_compile * 1000);
		coder->compile_count += 1;
	}
}

void	debug(t_coder *coder)
{
	if (coder->set->is_stopped != 1)
	{
		print_m(coder, 3);
		usleep(coder->set->time_to_debug * 1000);
	}
}

void	refactor(t_coder *coder)
{
	if (coder->set->is_stopped != 1)
	{
		print_m(coder, 4);
		usleep(coder->set->time_to_refactor * 1000);
	}
}

void	burn_out(t_coder *coder)
{
	if (coder->set->is_stopped != 1)
	{
		print_m(coder, 5);
		coder->is_burnout = 1;
		coder->set->is_stopped = 1;
	}
}
