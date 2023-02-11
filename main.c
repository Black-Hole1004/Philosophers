/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/11 19:01:07 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(size_t time)
{
	size_t now;

	now = get_time_ms();
	while (1) {

		if ((get_time_ms() - now) >= time)
			break ;
		usleep(15);
	}
}

// void leaks()
// {
// 	system("leaks philo | grep total");
// }

int main(int argc, char **argv)
{
	t_info  info;
	t_list  philos;
	t_list	*temp;
	int		i;

	if (argc < 5 || argc > 6 || pars(argc, argv) == -1)
	{
		printf("You didn't provide the right arguments\n");
		return (0);
	}
	if (!init_info(argc, argv, &info))
		return (0);
	// atexit(leaks);
	philos = *get_list(&philos, &info);
	i = 0;
	temp = &philos;
	loop(temp, info);
	return 0;
}