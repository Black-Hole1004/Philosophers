/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/18 14:25:33 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_info info)
{
	sem_close(info.semaphores);
	sem_close(info.print);
	sem_unlink("sem");
	sem_unlink("print");
}

void	put_fork(t_info *infos)
{
	sem_wait(infos->print);
	printf("\033[1;36m%zums| philo num: %d is sleeping\033[0m\n",
		time_diff(infos->t0), infos->index);
	sem_post(infos->print);
	my_usleep(infos->time_to_sleep);
	sem_wait(infos->print);
	printf("\033[1;37m%zums| philo num: %d is thinking\033[0m\n",
		time_diff(infos->t0), infos->index);
	sem_post(infos->print);
}

void	take_fork(t_info *infos)
{
	sem_wait(infos->semaphores);
	sem_wait(infos->semaphores);
	my_usleep(3);
	sem_wait(infos->print);
	printf("\033[1;35m%zums| philo num: %d has taken a fork\033[0m\n",
		time_diff(infos->t0), infos->index);
	printf("\033[1;34m%zums| philo num: %d is eating\033[0m\n",
		time_diff(infos->t0), infos->index);
	sem_post(infos->print);
	my_usleep(infos->time_to_eat);
	sem_post(infos->semaphores);
	sem_post(infos->semaphores);
}

void	loop_wait(t_info info)
{
	short	eats;
	int		status;

	eats = 0;
	while (1)
	{
		if (eats == info.time_eats)
		{
			printf("\033[1;32m All philosophers ate %d times\n\033[0m",
				info.time_eats);
			destroy_sem(info);
			my_usleep(500);
			kill(0, SIGINT);
		}
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DIED)
		{
			destroy_sem(info);
			my_usleep(500);
			kill(0, SIGINT);
		}
		else if (WEXITSTATUS(status) == FINISHED_EATING)
			eats++;
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6 || pars(argc, argv) == -1)
	{
		printf("You didn't provide the right arguments\n");
		return (0);
	}
	if (!init_info(argc, argv, &info))
		return (0);
	create_processes(&info);
	loop_wait(info);
	system("leaks philo_bonus");
	return (0);
}
