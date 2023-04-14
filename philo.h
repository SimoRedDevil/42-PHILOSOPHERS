/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:07:45 by mel-yous          #+#    #+#             */
/*   Updated: 2023/04/13 21:13:30 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef unsigned short	t_bool;
# define FALSE 0
# define TRUE 1

typedef struct s_args
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	unsigned int	total_meals;
	pthread_mutex_t	*misc_mutex;
	t_bool			is_alive;
}	t_args;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		soul;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	start_time;
	unsigned long	last_meal;
	struct s_args	*args;
}	t_philo;

int				ft_atoi(const char *str);
t_bool			args_checker(int ac, char **av);
unsigned long	timestamp(void);
void			meas_cleaner(t_philo *philo, pthread_mutex_t *mutexes, int n);
void			mutexed_print(char *msg, t_philo *philo);
t_bool			init_all(t_args *args, t_philo **philo, int ac, char **av);
void			mili_sleep(unsigned int sleep_time);
t_bool			create_threads(t_args *args, t_philo **philo);
void			soul_taker(t_philo *philo, t_args *args);

#endif