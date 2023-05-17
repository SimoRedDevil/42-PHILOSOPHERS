/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:35 by mel-yous          #+#    #+#             */
/*   Updated: 2023/05/17 17:43:36 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_done(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(philo[i].death_lock);
		if (philo[i].meals_counter < (unsigned int)data->must_eat)
			return (pthread_mutex_unlock(philo[i].death_lock), FALSE);
		pthread_mutex_unlock(philo[i].death_lock);
		i++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*locks;
	t_philo			*philo;
	pthread_t		*threads;
	int				i;

	if (args_checker(argc, argv) == FALSE)
		return (printf("%s", ERROR_MSG));
	init_data(argc, argv, &data);
	forks = init_mutexes(data.nb_philo);
	if (!forks)
		return (printf("%s", ERROR_MSG));
	locks = init_mutexes(data.nb_philo);
	if (!locks)
		return (destroyer(forks, data.nb_philo), printf("%s", ERROR_MSG));
	philo = init_philo(&data, forks, locks);
	if (!philo)
		return (printf("%s", ERROR_MSG));
	threads = create_threads(philo);
	if (!threads)
		return (destroyer(forks, data.nb_philo),
			destroyer(locks, data.nb_philo),
			free(philo), printf("%s", ERROR_MSG));
	i = 0;
	while (1)
	{
		if (i == data.nb_philo)
			i = 0;
		pthread_mutex_lock(philo[i].death_lock);
		if (get_current_time() - philo[i].last_meal
			>= (unsigned int)data.time_die)
		{
			data.is_alive = FALSE;
			printf("%lu %u died\n", get_current_time() - philo[i].start_time,
				philo[i].id);
			pthread_mutex_unlock(philo[i].death_lock);
			return (0);
		}
		pthread_mutex_unlock(philo[i].death_lock);
		if (is_done(philo, &data) == TRUE)
			break ;
		i++;
	}
	return (0);
}
