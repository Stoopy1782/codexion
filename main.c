/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 16:51:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/02 20:07:55 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_values(t_set *set, char **argv)
{
	set->number_of_coders = atoi(argv[1]);
	set->time_to_burnout = atoi(argv[2]);
	set->time_to_compile = atoi(argv[3]);
	set->time_to_debug = atoi(argv[4]);
	set->time_to_refactor = atoi(argv[5]);
	set->number_of_compiles_required = atoi(argv[6]);
	set->dongle_cooldown = atoi(argv[7]);
	set->is_stopped = 0;
}

int	init_scheduler(t_set *set, char *option)
{
	if (strcmp(option, "fifo") == 0)
	{
		set->scheduler = "fifo";
		return (0);
	}
	else if (strcmp(option, "edf") == 0)
	{
		set->scheduler = "edf";
		return (0);
	}
	return (1);
}

char	*validate_values(t_set *set)
{
	if (set->number_of_coders <= 1)
		return ("Number of coders needs at least 1.\n");
	if (set->time_to_burnout <= 0)
		return ("Time to burnout must take natural number.\n");
	if (set->time_to_compile <= 0)
		return ("Time to compile must take natural number.\n");
	if (set->time_to_debug <= 0)
		return ("Time to debug must take natural number.\n");
	if (set->time_to_refactor <= 0)
		return ("Time to refactor must take natural number.\n");
	if (set->number_of_compiles_required <= 0)
		return ("Number of compiles required must take natural number.\n");
	if (set->dongle_cooldown <= 0)
		return ("Dongle cooldown required must take natural number.\n");
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
	set_values(set, argv);
	val = validate_values(set);
	if (strcmp(val, "OK") != 0)
	{
		printf("%s", val);
		return (0);
	}
	else if (init_scheduler(set, argv[8]) != 0)
	{
		printf("Scheduler is invalid. Use 'edf' or 'fifo'.\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_set	set;
	t_dongle	*dongles;
	t_coder	*coders;

	memset(&set, 0, sizeof(t_set));
	if (parse_args(&set, argc, argv) == 0)
		return (0);
	set.start_time = get_time();
	dongles = create_dondles(&set);
	if (!dongles)
		return (1);
	coders = create_coders(&set, dongles);
	if (!coders)
	{
		free(dongles);
		return (1);
	}
	start_simulation(&set, coders);
	return (0);
}
