/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/10 20:45:25 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void *thread_func(void	*threads)
{
	t_list 			*thread;
	// struct timespec sleepTime;

	// struct timeval	t;
	// struct timeval	t2;
	size_t	t1;
	size_t	t2;
	int		mutex;

	thread = (t_list *)threads;
	if (thread->info->stop || thread->info->philo_num == 1)
		return (printf("philo num : 1 died\n"),
				thread->info->stop = 1, NULL);
	t1 = get_time_ms();
	if (thread->index % 2)
		usleep(100);
	// printf("beginnig : %zu\n", t1-thread->info->t0);
	while (1)
	{
		if (thread->index == thread->info->philo_num)
			mutex = 0;
		else
			mutex = thread->index - 1;
		// printf("mutex %d mutex_next %d\n", mutex,mutex + 1);
		if (!pthread_mutex_lock(&thread->info->mutex[mutex])
			&& !pthread_mutex_lock(&thread->info->mutex[mutex + 1]))
		{
			t2 = get_time_ms();
			if ((int)(t2 - t1) > thread->info->time_to_die)
				return (printf("philo num : %d died\n", thread->index),
				thread->info->stop = 1, NULL);
			printf("philo num: %d has taken a fork\n", thread->index);
			printf("philo num: %d is eating\n", thread->index);
			t1 = t2;
			usleep(thread->info->time_to_eat * 1000);
			thread->num_eats++;
			printf("philo num: %d is sleeping\n", thread->index);
			pthread_mutex_unlock(&thread->info->mutex[mutex]);
			pthread_mutex_unlock(&thread->info->mutex[mutex + 1]);
			usleep(thread->info->time_to_sleep * 1000);
			printf("philo num: %d is thinking\n", thread->index);
		}
		// else
		// {
		// 	printf("philo num : %d died\n", thread->index);
		// 	thread->info->stop = 1;
		// 	break ;
		// }
	}
	return NULL;
}

int main(int argc, char **argv)
{
	/* info members :
	   -philo numbers
	   -time to die
	   -time to eat
	   -time to sleep
	   -time of eats (optional) */
	// struct timeval	t;
	// struct timeval	t3;
	// struct timezone t2;
	t_info  info;
	t_list  philos;
	t_list	*temp;
	int		i;

	if (argc < 5 || argc > 6 || pars(argc, argv) == -1)
	{
		printf("You didn't provide the right arguments\n");
		return (0);
	}
	if (!init_info(argc, argv, &info, &philos))
		return (0);
	philos = *get_list(&philos, &info);
	i = 0;
	// gettimeofday(&t, &t2);
	// printf("Before --> %ld %d \n", t.tv_sec, t.tv_usec);
	// sleep(1);
	// gettimeofday(&t3, &t2);
	// printf("After ---> %ld %d \n", t3.tv_sec-t.tv_sec, t.tv_usec);
	// printf("%d\n", info.philo_num);
	// i = -1;
	while (1)
	{
		temp = &philos;
		while (i < info.philo_num)
		{
			if (temp->num_eats == info.time_eats)
				i++;
			else
				break ;
			temp = temp->next;
		}
		if (info.stop || i == info.philo_num)
			return (0);
	}
	// while (++i < info.philo_num)
	// {
	// 	if (pthread_join(temp->content, NULL) != 0)
	// 		return (1);
	// 	temp = temp->next;
	// }
	// ft_lstclear(&philos, del);
	return 0;
}