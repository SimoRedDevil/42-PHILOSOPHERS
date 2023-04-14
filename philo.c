/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:07:48 by mel-yous          #+#    #+#             */
/*   Updated: 2023/04/14 02:38:41 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void func(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			*philo;
	int				i;

	atexit(func);
	if (args_checker(argc, argv) == TRUE)
	{
		i = 0;
		if (init_all(&args, &philo, argc, argv) == FALSE)
			return (1);
		if (create_threads(&args, &philo) == FALSE)
			return (1);
		soul_taker(philo, &args);
		pthread_mutex_unlock(args.misc_mutex);
		mutexed_print("died", philo);
		//exit(0);
		// while (i < args.nb_philo)
		// {
		// 	pthread_mutex_destroy(&philo[i].args->misc_mutex[i]);
		// 	pthread_mutex_destroy(&philo[i].left_fork[i]);
		// 	i++;
		// }
		// free(philo->args->misc_mutex);
		free(philo);
		philo = NULL;
		return (0);
	}
	printf("Something is wrong !\n");
	return (1);
}
