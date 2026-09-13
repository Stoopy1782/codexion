/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 16:51:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/09/13 14:01:35 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_scheduler(t_set *set, char *option)
{
	if (strcmp(option, "fifo") == 0)
		set->scheduler = 0;
	else if (strcmp(option, "edf") == 0)
		set->scheduler = 1;
	else
		set->scheduler = -1;
}

int	set_values(t_set *set, char **argv)
{
	set->is_stopped = 0;
	set->number_of_coders = safe_atoi(argv[1]);
	set->time_to_burnout = safe_atoi(argv[2]);
	set->time_to_compile = safe_atoi(argv[3]);
	set->time_to_debug = safe_atoi(argv[4]);
	set->time_to_refactor = safe_atoi(argv[5]);
	set->number_of_compiles_required = safe_atoi(argv[6]);
	set->dongle_cooldown = safe_atoi(argv[7]);
	init_scheduler(set, argv[8]);
	if (pthread_mutex_init(&set->lock_s, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&set->lock_stop, NULL) != 0)
		return (1);
	return (0);
}

char	*validate_values(t_set *set)
{
	if (set->number_of_coders <= 0)
		return ("Number of coders is invalid.\n");
	if (set->time_to_burnout <= 0)
		return ("Time to burnout is invalid.\n");
	if (set->time_to_compile <= 0)
		return ("Time to compile is invalid.\n");
	if (set->time_to_debug <= 0)
		return ("Time to debug is invalid.\n");
	if (set->time_to_refactor <= 0)
		return ("Time to refactor is invalid.\n");
	if (set->number_of_compiles_required <= 0)
		return ("Number of compiles is invalid.\n");
	if (set->dongle_cooldown < 0)
		return ("Dongle cooldown required is invalid.\n");
	if (set->scheduler < 0)
		return ("Scheduler is invalid. Use 'edf' or 'fifo'.\n");
	return ("OK");
}

int	parse_args(t_set *set, int argc, char **argv)
{
	char	*val;

	if (argc != 9)
	{
		printf("Arguments is invalid. Check README.MD.\n");
		return (0);
	}
	if (set_values(set, argv) == 1)
		return (0);
	val = validate_values(set);
	if (strcmp(val, "OK") != 0)
	{
		printf("%s", val);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_set		set;
	t_dongle	*dongles;
	t_coder		*coders;

	memset(&set, 0, sizeof(t_set));
	if (parse_args(&set, argc, argv) == 0)
		return (0);
	set.start_time = get_time();
	dongles = create_dongles(&set);
	if (!dongles)
		return (1);
	coders = create_coders(&set, dongles);
	if (!coders)
	{
		free(dongles);
		return (1);
	}
	start_simulation(&set, coders);
	free_all(&set, coders);
	return (0);
}
