/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:40:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/01 22:41:52 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
    int i;

	result = 0;
    i = 0;
	while (is_whitespace(*str))
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
		    return (-1);
	str++;
	}
	while (*str)
	{
        if (*str < '0' || *str > '9')
            return (-1);
		result *= 10;
		result += *str - '0';
		str++;
        i++;
        if (i > 10)
            return (-1);
	}
	return (result);
}

int pars(int argc, char **argv)
{
    int i;

    i = 0;
    if (ft_atoi(argv[1]) == 0)
        return (-1);
    while (++i < argc)
        if (ft_atoi(argv[i]) < 0)
            return (-1);
    return (0);
}