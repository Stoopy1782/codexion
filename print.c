/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 14:45:58 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/03 18:03:44 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*get_message(int option)
{
	if (option == 1)
		return ("has taken a dongle");
	if (option == 2)
		return ("is compiling");
	if (option == 3)
		return ("is debugging");
	if (option == 4)
		return ("is refactoring");
	return (NULL);
}

int	check_stopped(t_coder *coder, int option, long now)
{
	if (option == 5)
	{
		printf("%ld %d burned out\n", now - coder->set->start_time,
			coder->id);
		pthread_mutex_unlock(&coder->set->lock_s);
		return (0);
	}
	if (is_stopped(coder->set) != 0)
	{
		pthread_mutex_unlock(&coder->set->lock_s);
		return (0);
	}
	return (1);
}

void	print_m(t_coder *coder, int option)
{
	long		now;
	const char	*message;

	pthread_mutex_lock(&coder->set->lock_s);
	now = get_time();
	if (check_stopped(coder, option, now) == 0)
		return ;
	message = get_message(option);
	if (message == NULL)
	{
		pthread_mutex_unlock(&coder->set->lock_s);
		return ;
	}
	printf("%ld %d %s\n", now - coder->set->start_time, coder->id,
		message);
	pthread_mutex_unlock(&coder->set->lock_s);
}
