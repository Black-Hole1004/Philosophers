/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:45:11 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/08 15:58:57 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_info
{
	int				philo_num;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				time_eats;
	pthread_mutex_t	*mutex;
}			t_info;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	t_info			*info;
	int				index;
	int				num_eats;
}			t_list;

void	*thread_func(void *thread);
t_list	*new_mutex(t_info *info, int i);
t_list	*new_thread(t_info *info, int i);
t_list	*get_list(t_list *list, t_info *info);
void	init_info(int argc, char **argv, t_info *info, t_list *philos);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstnew(void	*content);
int		ft_lstsize(t_list *lst);
int		pars(int argc, char **argv);
#endif