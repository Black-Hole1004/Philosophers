/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:58:13 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/20 12:16:56 by ahmaymou         ###   ########.fr       */
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
	sem_unlink("print");
	info->semaphores = sem_open("sem", O_CREAT, 0644, info->philo_num);
	info->print = sem_open("print", O_CREAT, 0644, 1);
	return (1);
}

int	loop(t_info *info)
{
	while (1)
	{
		if ((int)(get_time_ms() - info->last_eat) >= info->time_to_die)
		{
			sem_wait(info->print);
			printf("\033[1;31m%zums| philo num : %d died\033[0m\n",
				time_diff(info->t0), info->index);
			exit (DIED);
		}
		else if (info->time_eats != -1 && info->num_eats == info->time_eats)
			exit (FINISHED_EATING);
		usleep(100);
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
