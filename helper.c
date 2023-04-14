/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:07:03 by mel-yous          #+#    #+#             */
/*   Updated: 2023/04/13 23:24:58 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		else if (result > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return ((int)result * sign);
}

unsigned long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mili_sleep(unsigned int sleep_time)
{
	unsigned long	time;

	time = timestamp();
	while (timestamp() - time < sleep_time)
		usleep(sleep_time / 10);
}

void	mutexed_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->misc_mutex[philo->id - 1]);
	printf("%lu %d %s\n", timestamp() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->args->misc_mutex[philo->id - 1]);
}

void	meas_cleaner(t_philo *philo, pthread_mutex_t *mutexes, int n)
{
	int	i;

	i = 0;
	if (!philo && mutexes)
	{
		while (i < n)
			pthread_mutex_destroy(&mutexes[i++]);
		free(mutexes);
	}
	if (philo && !mutexes)
	{
		while (i < n)
			pthread_mutex_destroy(philo[i++].left_fork);
		free(philo);
	}
}
