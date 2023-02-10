/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/10 16:35:40 by ahmaymou         ###   ########.fr       */
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
	// struct timeval	t;
	// struct timeval	t2;
	size_t	t1;
	size_t	t2;

	thread = (t_list *)threads;
	t1 = get_time_ms();
	if (thread->info->stop)
		return (NULL);
	if (thread->index % 2)
		usleep(500);
	while (1)
	{
		if (pthread_mutex_lock(&thread->info->mutex[thread->index - 1]))
		{
			thread->info->stop = 1;
			return (printf("philo num : 1 died\n"), NULL);
		}
		if (pthread_mutex_lock(&thread->info->mutex[thread->index]))
		{
			thread->info->stop = 1;
		printf("sui\n");
			return(printf("philo num : 1 died\n"), NULL);
		}
		printf("philo num: %d has taken a fork\n", thread->index);
		t2 = get_time_ms();
		if ((int)(t2 - t1) >= thread->info->time_to_die)
		{
			printf("philo num : %d died\n", thread->index);
			// printf("t2 %lu ms t %ld diff %lu time_to_die %dms\n", t2,  t1, t2-t1, thread->info->time_to_die);
			thread->info->stop = 1;
			return NULL;
		}
		printf("philo num: %d is eating\n", thread->index);
		usleep(thread->info->time_to_eat * 1000);
		t1 = get_time_ms();
		thread->num_eats++;
		pthread_mutex_unlock(&thread->info->mutex[thread->index - 1]);
		pthread_mutex_unlock(&thread->info->mutex[thread->index]);
		printf("philo num: %d is sleeping\n", thread->index);
		usleep(thread->info->time_to_sleep * 1000);
		printf("philo num: %d is thinking\n", thread->index);
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