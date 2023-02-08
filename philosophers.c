/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:40:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/08 19:13:21 by ahmaymou         ###   ########.fr       */
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
	if (pthread_create(&thread, NULL, thread_func, (void *)new) != 0)
		return (NULL);
	return (new);
}

t_list	*new_mutex(t_info *info, int i)
{
	pthread_mutex_t	mutex;
	t_list			*new;

	pthread_mutex_init(&mutex, NULL);
	new = ft_lstnew(&mutex);
	new->info = info;
	new->index = i;
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

void	init_info(int argc, char **argv, t_info *info, t_list *philos)
{
	int	i;
	(void)philos;

	i = -1;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->time_eats = ft_atoi(argv[5]);
	info->mutex = malloc (info->philo_num * sizeof(pthread_mutex_t));
	while (++i < info->philo_num)
		pthread_mutex_init(&info->mutex[i], NULL);
}