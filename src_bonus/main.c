/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/16 14:44:12 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo_bonus");
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
			printf("All philosophers ate %d times\n", info.time_eats);
			sem_close(info.semaphores);
			sem_unlink("sem");
			kill(0, SIGINT);
		}
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DIED)
		{
			sem_close(info.semaphores);
			sem_unlink("sem");
			kill(0, SIGINT);
		}
		else if (WEXITSTATUS(status) == FINISHED_EATING)
			eats++;
		usleep(15);
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
	atexit(leaks);
	loop_wait(info);
	return (0);
}
