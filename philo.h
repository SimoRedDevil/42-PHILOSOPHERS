#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FALSE 0
# define TRUE 1
typedef unsigned short t_bool;

# define MUTEX_SIZE sizeof(pthread_mutex_t)
# define THREAD_SIZE sizeof(pthread_t)
# define PHILO_SIZE sizeof(t_philo)

typedef struct s_args
{
    int nb_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int must_eat;
} t_args;

typedef struct s_utils
{
    pthread_mutex_t *print_mtx;
    pthread_mutex_t *death_mtx;
} t_utils;

typedef struct s_philo
{
    unsigned int id;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    struct s_args *args;
    struct s_utils *utils;
} t_philo;

t_bool	args_checker(int ac, char **av);

int	ft_atoi(const char *str);
void meas_cleaner(pthread_mutex_t *arr, int n);

#endif