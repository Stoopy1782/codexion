/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:45:42 by ykojima           #+#    #+#             */
/*   Updated: 2026/09/03 16:54:12 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	is_overflow(int sign, long l, char next)
{
	if (sign == 1)
	{
		if (INT_MAX / 10 < l
			|| (INT_MAX / 10 == l && (INT_MAX % 10) < next - '0'))
			return (1);
	}
	else if (sign == -1)
	{
		if (INT_MAX / 10 < l
			|| (INT_MAX / 10 == l && 8 < next - '0'))
			return (-1);
	}
	return (0);
}

int	safe_atoi(const char *str)
{
	long	ret;
	int		sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		if (is_overflow(sign, ret, *str) != 0)
			return (-1);
		ret = ret * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((int)(ret * sign));
}
