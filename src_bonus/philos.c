/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:54:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/16 18:40:41 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (*str == ' ')
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

int	pars(int argc, char **argv)
{
	int	i;

	i = 0;
	if (ft_atoi(argv[1]) == 0)
		return (-1);
	while (++i < argc)
		if (ft_atoi(argv[i]) < 0)
			return (-1);
	return (0);
}

void	my_usleep(size_t time)
{
	size_t	now;

	now = get_time_ms();
	while (1)
	{
		if ((get_time_ms() - now) >= time)
			break ;
		usleep(30);
	}
}

void	*routine(void *info)
{
	t_info	*infos;

	infos = (t_info *)info;
	if (infos->index % 2)
		usleep(100);
	while (1)
	{
		take_fork(infos);
		infos->last_eat = get_time_ms();
		infos->num_eats++;
		put_fork(infos);
	}
	return (NULL);
}
