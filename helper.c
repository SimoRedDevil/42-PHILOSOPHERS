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

void meas_cleaner(pthread_mutex_t *arr, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&arr[i]);
		i++;
	}
	free(arr);
}
