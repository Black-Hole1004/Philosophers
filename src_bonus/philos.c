/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:54:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/15 19:28:59 by ahmaymou         ###   ########.fr       */
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
		usleep(15);
	}
}

void	*routine(void *info)
{
	t_info	*infos;

	infos = (t_info *)info;
	while (1)
	{
		sem_wait(infos->semaphores);
		sem_wait(infos->semaphores);
		printf("%dms philo num: %d has taken a fork\n",
			time_diff(infos->t0), infos->index);
		printf("%dms philo num: %d is eating\n",
			time_diff(infos->t0), infos->index);
		infos->last_eat = get_time_ms();
		my_usleep(infos->time_to_eat);
		sem_post(infos->semaphores);
		sem_post(infos->semaphores);
		infos->num_eats++;
		printf("%dms philo num: %d is sleeping\n",
			time_diff(infos->t0), infos->index);
		my_usleep(infos->time_to_sleep);
		printf("%dms philo num: %d is thinking\n",
			time_diff(infos->t0), infos->index);
	}
	return (NULL);
}
