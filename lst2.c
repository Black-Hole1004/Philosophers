/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:24:22 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/11 17:02:34 by ahmaymou         ###   ########.fr       */
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