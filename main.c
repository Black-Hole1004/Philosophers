/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:47:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/02/01 22:33:58 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread_func(void *arg) {
    (void)arg;
    // printf("Waiting\n");
    while (1)
    {
        sleep(2);
        puts("my turn");
        // printf("Finished, Argument was %d\n", *(int *)arg);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6 || pars(argc, argv) == -1)
    {
        write(1, "You didn't provide the right arguments\n", 40);
        return (0);
    }
    pthread_t thread;
    int arg = 42;
    int result = pthread_create(&thread, NULL, thread_func, &arg);

    if (result != 0) {
        printf("Error creating thread\n");
        return 1;
    }
    // printf("Thread created successfully\n");
    while (1) {
        sleep(2);
        puts("your turn");
    }
    pthread_join(thread, NULL);
    return 0;
}