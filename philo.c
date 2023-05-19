/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:35 by mel-yous          #+#    #+#             */
/*   Updated: 2023/05/19 12:26:21 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	is_done(t_philo *philo, t_data *data)
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

static t_bool	still_alive(int i, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo[i].death_lock);
	if (get_time() - philo[i].last_meal
		>= (unsigned int)data->time_die)
		return (pthread_mutex_unlock(philo[i].death_lock), FALSE);
	pthread_mutex_unlock(philo[i].death_lock);
	return (TRUE);
}

static void	print_death(t_philo *philo)
{
	printf("%lu %u died\n", get_time() - philo->start_time, philo->id);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*locks;
	t_philo			*philo;
	int				i;

	if (args_checker(argc, argv) == FALSE)
		return (printf("%s", ERROR_MSG));
	init_data(argc, argv, &data);
	if (init_all(&data, &forks, &locks, &philo) == FALSE)
		return (printf("%s", ERROR_MSG));
	if (create_threads(philo, &data, forks, locks) == FALSE)
		return (printf("%s", ERROR_MSG));
	i = 0;
	while (1)
	{
		if (i == data.nb_philo)
			i = 0;
		if (still_alive(i, philo, &data) == FALSE)
			return (data.is_alive = FALSE, print_death(&philo[i]), 0);
		if (data.must_eat > 0 && is_done(philo, &data) == TRUE)
			return (0);
		i++;
	}
}
