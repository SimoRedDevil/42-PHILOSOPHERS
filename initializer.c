/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:41:43 by mel-yous          #+#    #+#             */
/*   Updated: 2023/04/13 21:35:16 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initialize_args(t_args *args, int ac, char **av)
{
	args->nb_philo = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	args->must_eat = 0;
	args->total_meals = 0;
	args->is_alive = TRUE;
	if (ac == 6)
		args->must_eat = ft_atoi(av[5]);
}

static void	prepare_philo(t_args *args, t_philo **philo,
	pthread_mutex_t *forks, pthread_mutex_t *misc_mutex)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].args = args;
		(*philo)[i].left_fork = &forks[i];
		(*philo)[i].right_fork = &forks[(i + 1) % args->nb_philo];
		(*philo)[i].args->misc_mutex = misc_mutex;
		(*philo)[i].start_time = timestamp();
		(*philo)[i].last_meal = timestamp();
		i++;
	}
}

static t_bool	fuck_nomrinette(t_args *args, t_philo **philo,
	pthread_mutex_t *misc_mutex)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
		if (pthread_mutex_init(&misc_mutex[i++], NULL))
			return (meas_cleaner(NULL, misc_mutex, i), free(*philo), FALSE);
	return (TRUE);
}

static t_bool	init_philo(t_args *args, t_philo **philo)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*misc_mutex;
	int				i;

	forks = malloc(args->nb_philo * sizeof(pthread_mutex_t));
	if (!forks)
		return (FALSE);
	misc_mutex = malloc(args->nb_philo * sizeof(pthread_mutex_t));
	if (!misc_mutex)
		return (free(forks), FALSE);
	*philo = malloc(args->nb_philo * sizeof(t_philo));
	if (!*philo)
		return (free(misc_mutex), free(forks), FALSE);
	i = 0;
	while (i < args->nb_philo)
		if (pthread_mutex_init(&forks[i++], NULL))
			return (meas_cleaner(NULL, forks, i),
				free(misc_mutex), free(*philo), FALSE);
	if (fuck_nomrinette(args, philo, misc_mutex) == FALSE)
		return (meas_cleaner(NULL, forks, args->nb_philo), FALSE);
	prepare_philo(args, philo, forks, misc_mutex);
	return (TRUE);
}

t_bool	init_all(t_args *args, t_philo **philo, int ac, char **av)
{
	initialize_args(args, ac, av);
	if (init_philo(args, philo) == FALSE)
		return (FALSE);
	return (TRUE);
}
