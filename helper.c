/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:09 by mel-yous          #+#    #+#             */
/*   Updated: 2023/05/19 12:23:49 by mel-yous         ###   ########.fr       */
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

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mutexed_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->is_alive == TRUE)
		printf("%lu %u %s\n", get_time() - philo->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	my_usleep(unsigned int time)
{
	unsigned long	begin_time;

	begin_time = get_time();
	while (get_time() - begin_time < time)
		usleep(100);
}

void	destroyer(pthread_mutex_t *arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&arr[i++]);
	free(arr);
}
