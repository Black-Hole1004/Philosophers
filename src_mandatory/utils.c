/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:56:45 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/16 18:21:57 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	time_diff(size_t t0)
{
	size_t	t;

	t = get_time_ms();
	return (t - t0);
}

void	*thread_func(void	*threads)
{
	t_list	*thread;

	thread = (t_list *)threads;
	if (thread->index % 2)
		usleep(100);
	while (1)
	{
		take_forks(thread);
		thread->last_eat = get_time_ms();
		thread->num_eats++;
		put_forks(thread);
	}
	return (NULL);
}

bool	check_eats(t_info *info, t_list *philos)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (philos->num_eats < info->time_eats)
			return (false);
		philos = philos->next;
	}
	return (true);
}

void	destroy(t_list	**temp, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_mutex_destroy(&(*temp)->mutex))
			return ;
		(*temp) = (*temp)->next;
	}
	ft_lstclear(temp);
}
