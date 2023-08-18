#include "philosophers_header.h"

void    come_eat(t_perso *perso)
{
    print(perso->id, "is eating", perso);
    pthread_mutex_lock(&perso->base->run);
    perso->last_meal = get_time() - perso->time_start;
    pthread_mutex_unlock(&perso->base->run);
    usleep(perso->time_to_eat * 1000);
}

void	go_sleep(t_perso *perso)
{
	print(perso->id, "is sleeping", perso);
	usleep(perso->time_to_sleep * 1000);
	print(perso->id, "is thinking", perso);
}

void    take_fork(t_perso *perso)
{
	pthread_mutex_lock(&perso->base->fork[perso->f_fork]);
	print(perso->id, "has taken a fork", perso);
	pthread_mutex_lock(&perso->base->fork[perso->s_fork]);
	print(perso->id, "has taken a fork", perso);
	come_eat(perso);
	pthread_mutex_unlock(&perso->base->fork[perso->s_fork]);
	pthread_mutex_unlock(&perso->base->fork[perso->f_fork]);
}

void *routine(void *per)
{
    t_perso *perso;

    perso = (t_perso *)per;
    pthread_mutex_lock(&perso->base->run);
    while (perso->how_much_eat != 0 && perso->base->is_dead == -1)
    {
        pthread_mutex_unlock(&perso->base->run);
        take_fork(perso);
        go_sleep(perso);
        pthread_mutex_lock(&perso->base->run);
        perso->how_much_eat -= 1;
    }
    pthread_mutex_unlock(&perso->base->run);
    return NULL;
}