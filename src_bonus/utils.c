/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:58:13 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/16 14:58:03 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	time_diff(size_t t0)
{
	size_t	t;

	t = get_time_ms();
	return (t - t0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->time_eats = ft_atoi(argv[5]);
		if (!(info->time_eats))
			return (0);
	}
	else
		info->time_eats = -1;
	info->t0 = get_time_ms();
	info->last_eat = info->t0;
	sem_unlink("sem");
	info->semaphores = sem_open("sem", O_CREAT, 0644, info->philo_num);
	return (1);
}

int	loop(t_info *info)
{
	while (1)
	{
		if ((int)(get_time_ms() - info->last_eat) >= info->time_to_die)
		{
			printf("%dms philo num : %d died\n",
				time_diff(info->t0), info->index);
			exit (DIED);
		}
		else if (info->time_eats != -1 && info->num_eats == info->time_eats)
			exit (FINISHED_EATING);
	}
}

void	create_processes(t_info *info)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < info->philo_num)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Error creating process\n");
			return ;
		}
		else if (pid == 0)
		{
			info->index = i + 1;
			if (pthread_create(&info->thread, NULL, routine, (void *)info))
				return ;
			if (pthread_detach(info->thread))
				return ;
			loop(info);
		}
	}
}
