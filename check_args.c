/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:38:40 by mel-yous          #+#    #+#             */
/*   Updated: 2023/04/13 20:33:07 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	check_sign_and_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' || av[i][j] == '+')
			{
				if (av[i][j - 1])
					return (FALSE);
				j++;
			}
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

static t_bool	check_args_values(int ac, char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) >= 200 || ft_atoi(av[2]) < 0
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (FALSE);
	if (ac == 6)
		if (ft_atoi(av[5]) <= 0)
			return (FALSE);
	return (TRUE);
}

t_bool	args_checker(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (FALSE);
	if (check_sign_and_digits(av) == FALSE)
		return (FALSE);
	if (check_args_values(ac, av) == FALSE)
		return (FALSE);
	return (TRUE);
}
