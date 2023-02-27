/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/17 18:25:47 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(size_t time)
{
	size_t	now;

	now = get_time_ms();
	while (1)
	{
		if ((get_time_ms() - now) >= time)
			break ;
		usleep(30);
	}
}

// void leaks()
// {
// 	system("leaks philo | grep total");
// }

int	main(int argc, char **argv)
{
	t_info	info;
	t_list	philos;

	if (argc < 5 || argc > 6 || pars(argc, argv) == -1)
	{
		printf("You didn't provide the right arguments\n");
		return (0);
	}
	if (!init_info(argc, argv, &info))
		return (0);
	philos = *get_list(&philos, &info);
	loop(&philos, info);
	return (0);
}
