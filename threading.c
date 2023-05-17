/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:46 by mel-yous          #+#    #+#             */
/*   Updated: 2023/05/17 21:47:27 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	mutexed_print(philo, "has taken a fork");
	if (philo->data->nb_philo > 1)
	{
		pthread_mutex_lock(philo->r_fork);
		mutexed_print(philo, "has taken a fork");
	}
}

static void	eat_sleep_think(t_philo *philo)
{
	mutexed_print(philo, "is eating");
	pthread_mutex_lock(philo->death_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->death_lock);
	my_usleep(philo->data->time_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	mutexed_print(philo, "is sleeping");
	my_usleep(philo->data->time_sleep);
	mutexed_print(philo, "is thinking");
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		pickup_forks(philo);
		if (philo->data->nb_philo > 1)
		{
			eat_sleep_think(philo);
			if (philo->data->must_eat > 0)
			{
				pthread_mutex_lock(philo->death_lock);
				philo->meals_counter++;
				if (philo->meals_counter >= (unsigned int)philo->data->must_eat)
				{
					pthread_mutex_unlock(philo->death_lock);
					break ;
				}
				pthread_mutex_unlock(philo->death_lock);
			}
		}
	}
	return (NULL);
}
