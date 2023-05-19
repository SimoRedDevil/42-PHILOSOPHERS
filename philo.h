/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:01:38 by mel-yous          #+#    #+#             */
/*   Updated: 2023/05/19 10:30:30 by mel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR_MSG "Something is wrong !\n"

typedef short	t_bool;
# define FALSE 0
# define TRUE 1

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	t_bool			is_alive;

	pthread_mutex_t	print_lock;
}	t_data;

typedef struct s_philo
{
	unsigned int	id;
	unsigned long	start_time;
	unsigned long	last_meal;
	unsigned int	meals_counter;

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*death_lock;

	struct s_data	*data;
}	t_philo;

int				ft_atoi(const char *str);
unsigned long	get_time(void);
void			destroyer(pthread_mutex_t *arr, int n);
void			mutexed_print(t_philo *philo, char *msg);
void			my_usleep(unsigned int time);

t_bool			args_checker(int ac, char **av);

void			init_data(int ac, char **av, t_data *data);
pthread_mutex_t	*init_mutexes(int nb_philo);
t_philo			*init_philo(t_data *data, pthread_mutex_t *forks,
					pthread_mutex_t *locks);
t_bool			init_all(t_data *data, pthread_mutex_t **forks,
					pthread_mutex_t **locks, t_philo **philo);

void			*routine(void *param);
t_bool			create_threads(t_philo *philo, t_data *data,
					pthread_mutex_t *forks, pthread_mutex_t *locks);

#endif