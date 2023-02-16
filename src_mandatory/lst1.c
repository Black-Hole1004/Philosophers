/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:24:17 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/15 19:00:03 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = ft_lstlast(*lst);
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		new->next = new;
	}
	else
	{
		new->next = *lst;
		temp->next = new;
		*lst = new;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	new->next = *lst;
	temp = *lst;
	if ((*lst))
	{
		while (1)
		{
			temp = temp->next;
			if (temp->next == *lst)
				break ;
		}
		temp->next = new;
	}
	else
		*lst = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = lst->next;
	if (!lst)
		return (NULL);
	while (temp->next != lst)
		temp = temp->next;
	return (temp);
}

void	put_forks(t_list *thread)
{
	pthread_mutex_unlock(&thread->mutex);
	pthread_mutex_unlock(&thread->next->mutex);
}
