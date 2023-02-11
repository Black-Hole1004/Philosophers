/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/11 17:40:19 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	time_diff(size_t t0)
{
	size_t	t;

	t = get_time_ms();
	return (t-t0);
}

void	my_usleep(size_t time)
{
	size_t now;

	now = get_time_ms();
	while (1) {

		if ((get_time_ms() - now) >= time)
			break ;
		usleep(15);
	}
}

void *thread_func(void	*threads)
{
	t_list 			*thread;

	thread = (t_list *)threads;
	if (thread->index % 2)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&thread->mutex);
		pthread_mutex_lock(&thread->next->mutex);
		if (thread->info->stop)
			return (NULL);
		printf("%dms philo num: %d has taken a fork\n", time_diff(thread->info->t0), thread->index);
		printf("%dms philo num: %d is eating\n", time_diff(thread->info->t0), thread->index);
		thread->last_eat = get_time_ms();
		my_usleep(thread->info->time_to_eat);
		pthread_mutex_unlock(&thread->mutex);
		pthread_mutex_unlock(&thread->next->mutex);
		thread->num_eats++;
		printf("%dms philo num: %d is sleeping\n", time_diff(thread->info->t0), thread->index);
		my_usleep(thread->info->time_to_sleep);
		printf("%dms philo num: %d is thinking\n", time_diff(thread->info->t0), thread->index);
	}
	return NULL;
}

bool	check_eats(t_info *info, t_list *philos)
{
	int i;

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

void leaks()
{
	system("leaks philo | grep total");
}

int main(int argc, char **argv)
{
	t_info  info;
	t_list  philos;
	t_list	*temp;
	int		i;

	if (argc < 5 || argc > 6 || pars(argc, argv) == -1)
	{
		printf("You didn't provide the right arguments\n");
		return (0);
	}
	if (!init_info(argc, argv, &info))
		return (0);
	// atexit(leaks);
	philos = *get_list(&philos, &info);
	i = 0;
	temp = &philos;
	while (1)
	{
		if ((int)(get_time_ms() - temp->last_eat) >= info.time_to_die)
		{
			info.stop = 1;
			printf("%dms philo num : %d died\n", time_diff(info.t0), temp->index);
			return (destroy(&temp, &info), 0);
		}
		else if (info.time_eats != -1 && check_eats(&info, temp))
		{
			info.stop = 1;
			usleep(100);
			printf("All philosophers ate\n");
			return (destroy(&temp, &info), 0);
		}
		temp = temp->next;
	}
	// ft_lstclear(&temp);
	return 0;
}