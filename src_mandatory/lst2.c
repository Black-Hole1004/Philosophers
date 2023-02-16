/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:24:22 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/16 18:23:34 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = elem;
	return (elem);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	int		len;

	len = ft_lstsize(*lst);
	if (!lst)
		return ;
	while (len && lst)
	{
		temp = (*lst)->next;
		free(*lst);
		(*lst) = temp;
		len--;
	}
	free(lst);
	lst = NULL;
}

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		count;

	temp = lst;
	count = 0;
	if (lst == NULL)
		return (0);
	while (1)
	{
		count++;
		temp = temp->next;
		if (temp == lst)
			break ;
	}
	return (count);
}

int	loop(t_list *temp, t_info info)
{
	while (1)
	{
		if ((int)(get_time_ms() - temp->last_eat) >= info.time_to_die)
		{
			info.stop = 1;
			printf("\033[1;31m%zums| philo num : %d died\033[0m\n",
				time_diff(info.t0), temp->index);
			return (destroy(&temp, &info), 0);
		}
		else if (info.time_eats != -1 && check_eats(&info, temp))
		{
			info.stop = 1;
			my_usleep(1);
			printf("\033[1;32m All philosophers ate %d times\n\033[0m", info.time_eats);
			return (destroy(&temp, &info), 0);
		}
		temp = temp->next;
	}
}

void	take_forks(t_list *thread)
{
	pthread_mutex_lock(&thread->mutex);
	pthread_mutex_lock(&thread->next->mutex);
	my_usleep(1);
	if (thread->info->stop)
		return ;
	printf("\033[1;35m%zums| philo num: %d has taken a fork\033[0m\n",
		time_diff(thread->info->t0), thread->index);
	printf("\033[1;34m%zums| philo num: %d is eating\0331m\n",
		time_diff(thread->info->t0), thread->index);
	my_usleep(thread->info->time_to_eat);
	pthread_mutex_unlock(&thread->mutex);
	pthread_mutex_unlock(&thread->next->mutex);
}
