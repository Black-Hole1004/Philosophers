/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:40:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/11 17:31:05 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
    int i;

	result = 0;
    i = 0;
	while (*str == ' ')
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
		    return (-1);
	str++;
	}
	while (*str)
	{
        if (*str < '0' || *str > '9')
            return (-1);
		result *= 10;
		result += *str - '0';
		str++;
        i++;
        if (i > 10)
            return (-1);
	}
	return (result);
}

int pars(int argc, char **argv)
{
    int i;

    i = 0;
    if (ft_atoi(argv[1]) == 0)
        return (-1);
    while (++i < argc)
        if (ft_atoi(argv[i]) < 0)
            return (-1);
    return (0);
}

t_list	*new_thread(t_info *info, int i)
{
	pthread_t	thread;
	t_list		*new;

	new = ft_lstnew(&thread);
	new->info = info;
	new->index = i;
	new->dead = 0;
	new->last_eat = info->t0;
	new->num_eats = 0;
	if (pthread_mutex_init(&new->mutex, NULL))
		return (NULL);
	if (pthread_create(&thread, NULL, thread_func, (void *)new) != 0)
		return (NULL);
	return (new);
}

t_list	*get_list(t_list *list, t_info *info)
{
	int	i;

	i = 0;
	list = new_thread(info, 1);
	while (++i < info->philo_num)
		ft_lstadd_back(&list, new_thread(info, i+1));
	return (list);
}

int	init_info(int argc, char **argv, t_info *info)
{
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (!(info->time_eats = ft_atoi(argv[5])))
			return (0);
	}
	else
		info->time_eats = -1;
	info->t0 = get_time_ms();
	info->stop = 0;
	return (1);
}