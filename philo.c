#include "philo.h"

static void *routine(void *param)
{
    return (NULL);
}

int main(int argc, char **argv)
{
    t_args args;
    t_utils utils;

    pthread_mutex_t *forks;
    pthread_mutex_t print_mtx;
    pthread_mutex_t death_mtx;
    pthread_t *threads;

    t_philo *philo;
    int i;

    if (args_checker(argc, argv) == TRUE)
    {
        args.nb_philo = ft_atoi(argv[1]);
        args.time_die = ft_atoi(argv[2]);
        args.time_eat = ft_atoi(argv[3]);
        args.time_sleep = ft_atoi(argv[4]);
        args.must_eat = 0;
        if (argc == 6)
            args.must_eat = ft_atoi(argv[5]);
        i = 0;
        forks = malloc(args.nb_philo * MUTEX_SIZE);
        if (!forks)
            return (1);
        if (pthread_mutex_init(&print_mtx, NULL))
            return (free(forks), 1);
        if (pthread_mutex_init(&death_mtx, NULL))
            return (free(forks), (void)pthread_mutex_destroy(&print_mtx), 1);
        utils.print_mtx = &print_mtx;
        utils.death_mtx = &death_mtx;
        threads = malloc(args.nb_philo * THREAD_SIZE);
        philo = malloc(args.nb_philo * PHILO_SIZE);
        while (i < args.nb_philo)
        {
            pthread_mutex_init(&forks[i], NULL);
            i++;
        }
        i = 0;
        while (i < args.nb_philo)
        {
            philo[i].id = i + 1;
            philo[i].l_fork = &forks[i];
            philo[i].r_fork = &forks[(i + 1) % args.nb_philo];
            philo[i].args = &args;
            philo[i].utils = &utils;
            i++;
        }
        i = 0;
        while (i < args.nb_philo)
        {
            // pthread_create(&threads[i], NULL, &routine, &philo[i]);
            i++;
        }
        meas_cleaner(forks, args.nb_philo);
        pthread_mutex_destroy(&print_mtx);
        pthread_mutex_destroy(&death_mtx);
        free(threads);
        free(philo);
        return (0);
    }
    printf("Something is wrong\n");
    return (1);
}
