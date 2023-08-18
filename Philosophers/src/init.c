#include "philosophers_header.h"

int init_basic_var(char **av, t_struct *base)
{
    base->philo_number = ft_atoi(av[1]);
    base->time_to_die = ft_atoi(av[2]);
    base->time_to_eat = ft_atoi(av[3]);
    base->time_to_sleep = ft_atoi(av[4]);
    base->how_much_eat = -1;
    if (av[5])
        base->how_much_eat = ft_atoi(av[5]);
    base->is_dead = -1;
    pthread_mutex_init(&base->write, NULL);
    pthread_mutex_init(&base->run, NULL);
    base->time_start = get_time();
    base->is_okay = ft_atoi(av[1]);
    return (0);
}

int    init_alloc(t_struct *base)
{
    base->philosophe = malloc(sizeof(pthread_t) * base->philo_number);
    if (!base->philosophe)
        return (1);
    base->fork = malloc(sizeof(pthread_mutex_t) * base->philo_number);
    if (!base->fork)
        return (1);
    base->perso = malloc(sizeof(t_perso) * base->philo_number);
    if (!base->perso)
        return (1);
    return (0);
}

void    init_philo(t_struct *base)
{
    int i;

    i = 0;
    while(i < base->philo_number)
    {
        base->perso[i].base = base;
        base->perso[i].id = i + 1;
        base->perso[i].philo_number = base->philo_number;
        base->perso[i].time_to_die = base->time_to_die;
        base->perso[i].time_to_eat = base->time_to_eat;
        base->perso[i].time_to_sleep = base->time_to_sleep; 
        base->perso[i].how_much_eat = base->how_much_eat;
        base->perso[i].last_meal = base->time_start;
        base->perso[i].time_start = base->time_start;
        i++;
    }
}

int init_fork(t_struct *base)
{
    int i;

    i = 0;
    while (i < base->philo_number)
    {
        pthread_mutex_init(&base->fork[i], NULL);
        i++;
    }
    i = 1;
    while (i <= base->philo_number)
    {
        if (i % 2 == 0)
        {
            base->perso[i - 1].f_fork = i - 1;
            if (i == base->philo_number)
                base->perso[i - 1].s_fork = 0;
            else
                base->perso[i - 1].s_fork = i;
        }
        else
        {
            if (i == 1)
                base->perso[i - 1].f_fork = base->philo_number - 1;
            else
                base->perso[i - 1].f_fork = i - 2;
            base->perso[i - 1].s_fork = i - 1;
        }
        i++;
    }
    return (0);
}

int    init_thread(t_struct *base)
{
    int i;

    i = 0;
    while (i < base->philo_number)
    {
        if (pthread_create(&base->philosophe[i], NULL, &routine, &base->perso[i]))
            return (1);
        usleep(10);
        i++;
    }
    return (0);
}