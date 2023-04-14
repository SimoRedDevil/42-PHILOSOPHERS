/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:55:43 by mel-yous          #+#    #+#             */
/*   Updated: 2023/04/13 23:24:22 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	mutexed_print("has taken a fork", philo);
	if (philo->args->nb_philo > 1)
	{
		pthread_mutex_lock(philo->right_fork);
		mutexed_print("has taken a fork", philo);
	}
}

static void	eat_sleep_think(t_philo *philo)
{
	if (philo->args->nb_philo > 1)
	{
		pthread_mutex_lock(&philo->args->misc_mutex[philo->id - 1]);
		philo->args->total_meals++;
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->args->misc_mutex[philo->id - 1]);
		mutexed_print("is eating", philo);
		mili_sleep(philo->args->time_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		mutexed_print("is sleeping", philo);
		mili_sleep(philo->args->time_sleep);
		mutexed_print("is thinking", philo);
	}
}

static void	*lifecycle(void *param)
{
	t_philo			*philo;
	unsigned long	i;

	philo = (t_philo *)param;
	i = 0;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->args->is_alive == TRUE)
	{
		take_forks(philo);
		eat_sleep_think(philo);
	}
	return (NULL);
}

t_bool	create_threads(t_args *args, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_create(&(*philo)[i].soul, NULL, lifecycle, &(*philo)[i]))
		{
			free(*philo);
			/* 1- Destroy mutexes
			   2- Free philo array
			*/
			return (FALSE);
		}
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
		pthread_detach((*philo)[i++].soul);
	return (TRUE);
}

void	soul_taker(t_philo *philo, t_args *args)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < args->nb_philo)
		{
			pthread_mutex_lock(&args->misc_mutex[i]);
			if (timestamp() - philo[i].last_meal >= (unsigned int)args->time_die)
			{
				philo[i].args->is_alive = FALSE;
				return ;
			}
			if (args->must_eat > 0)
			{
				if (args->total_meals >= (unsigned int)(args->must_eat * args->nb_philo))
				{
					philo[i].args->is_alive = FALSE;
					return ;
				}
			}
			pthread_mutex_unlock(&args->misc_mutex[i]);
			i++;
		}
		usleep(400);
	}
}
