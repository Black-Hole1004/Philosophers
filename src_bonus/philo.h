/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:45:11 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/17 16:46:38 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/types.h>

# define DIED			  1
# define FINISHED_EATING  2

typedef struct s_info
{
	int				philo_num;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				time_eats;
	size_t			t0;
	size_t			last_eat;
	int				num_eats;
	pthread_t		thread;
	int				index;
	int				eats;
	sem_t			*semaphores;
	sem_t			*print;
}			t_info;

size_t	get_time_ms(void);
void	*routine(void *info);
int		ft_atoi(const char *str);
size_t	time_diff(size_t t0);
void	my_usleep(size_t time);
int		init_info(int argc, char **argv, t_info *info);
int		pars(int argc, char **argv);
int		loop(t_info *info);
void	create_processes(t_info *info);
void	take_fork(t_info *infos);
void	put_fork(t_info *infos);
#endif