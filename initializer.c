/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:13 by mel-yous          #+#    #+#             */
/*   Updated: 2023/05/19 10:42:02 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	data->is_alive = TRUE;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	pthread_mutex_init(&data->print_lock, NULL);
}

pthread_mutex_t	*init_mutexes(int nb_philo)
{
	pthread_mutex_t	*arr;
	int				i;

	arr = malloc(nb_philo * sizeof(pthread_mutex_t));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < nb_philo)
		pthread_mutex_init(&arr[i++], NULL);
	return (arr);
}

t_philo	*init_philo(t_data *data, pthread_mutex_t *forks,
	pthread_mutex_t *locks)
{
	t_philo	*philo;
	int		i;

	philo = malloc(data->nb_philo * sizeof(t_philo));
	if (!philo)
		return (destroyer(forks, data->nb_philo),
			destroyer(locks, data->nb_philo), NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_counter = 0;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % data->nb_philo];
		philo[i].death_lock = &locks[i];
		philo[i].data = data;
		philo[i].start_time = get_time();
		philo[i].last_meal = get_time();
		i++;
	}
	return (philo);
}

t_bool	init_all(t_data *data, pthread_mutex_t **forks,
	pthread_mutex_t **locks, t_philo **philo)
{
	*forks = init_mutexes(data->nb_philo);
	if (!*forks)
		return (FALSE);
	*locks = init_mutexes(data->nb_philo);
	if (!*locks)
		return (destroyer(*forks, data->nb_philo), FALSE);
	*philo = init_philo(data, *forks, *locks);
	if (!*philo)
		return (FALSE);
	return (TRUE);
}

t_bool	create_threads(t_philo *philo, t_data *data,
	pthread_mutex_t *forks, pthread_mutex_t *locks)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(philo->data->nb_philo * sizeof(pthread_t));
	if (!threads)
		return (destroyer(forks, data->nb_philo),
			destroyer(locks, data->nb_philo), free(philo), FALSE);
	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_create(&threads[i], NULL, &routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->data->nb_philo)
		pthread_detach(threads[i++]);
	free(threads);
	return (TRUE);
}
