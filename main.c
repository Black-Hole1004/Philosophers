/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/08 20:44:34 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread_func(void	*threads)
{
	(void)threads;
	t_list 			*thread;
	struct timeval	t;

	thread = (t_list *)threads;
	gettimeofday(&t, NULL);
	while (1)
	{
		printf("%d %d has taken a fork\n", t.tv_usec, thread->index);
		pthread_mutex_lock(&thread->info->mutex[thread->index - 1]);
		pthread_mutex_lock(&thread->info->mutex[thread->index]);
		usleep(500);
		printf("%d %d is sleeping\n", t.tv_usec, thread->index);
		pthread_mutex_unlock(&thread->info->mutex[thread->index - 1]);
		pthread_mutex_unlock(&thread->info->mutex[thread->index]);
		// printf("Finished, Argument was %d\n", *(int *)arg);
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
	t_list  *philos = NULL;
	t_list	*temp;
	int		i;

	if (argc < 5 || argc > 6 || pars(argc, argv) == -1)
	{
		printf("You didn't provide the right arguments\n");
		return (0);
	}
	init_info(argc, argv, &info, philos);
	philos = get_list(philos, &info);
	i = 0;
	// gettimeofday(&t, &t2);
	// printf("Before --> %ld %d \n", t.tv_sec, t.tv_usec);
	// sleep(1);
	// gettimeofday(&t3, &t2);
	// printf("After ---> %ld %d \n", t3.tv_sec-t.tv_sec, t.tv_usec);
	printf("%d\n", info.philo_num);
	i = -1;
	temp = philos;
	// while (++i < info.philo_num)
	// {
	// 	// if (pthread_join(temp->content, NULL) != 0)
	// 	// 	return (1);
	// 	printf("%d\n", temp->index);
	// 	temp = temp->next;
	// }
	// ft_lstclear(&philos, del);
	return 0;
}