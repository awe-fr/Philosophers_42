#include "philosophers_header.h"

void    do_join(t_struct *base)
{
    int i;

    i = 0;
    while(i < base->philo_number)
    {
        pthread_join(base->philosophe[i], NULL);
        i++;
    }
}

void	ft_cancel(t_struct *base)
{
	int i;
	
	i = 0;
	while (i < base->philo_number)
	{
		pthread_mutex_destroy(&base->fork[i]);
		i++;
	}
	free(base->fork);
    free(base->perso);
    free(base->philosophe);
	pthread_mutex_destroy(&base->write);
	pthread_mutex_destroy(&base->run);
}

void    is_dead(t_struct *base)
{
    int i;

    i = 0;
    pthread_mutex_lock(&base->run);
    while (base->is_okay > 0 && base->is_dead == -1)
    {
        pthread_mutex_unlock(&base->run);
        while(i < base->philo_number)
        {
            pthread_mutex_lock(&base->run);
            if ((((get_time() - base->time_start) - base->perso[i].last_meal) >= base->time_to_die) && base->perso[i].how_much_eat != 0)
            {
		    	if (base->is_dead != -1)
		    	{
			        pthread_mutex_unlock(&base->run);
			    	return ;
		    	}
                base->is_dead = base->perso->id;
                pthread_mutex_lock(&base->write);
			    printf("%ld | %d | is dead\n", get_time() - base->time_start, base->is_dead);
			    pthread_mutex_unlock(&base->write);
                pthread_mutex_unlock(&base->run);
                return ;
            }
            else if(base->perso[i].how_much_eat == 0)
                base->is_okay--;
            pthread_mutex_unlock(&base->run);
            i++;
        }
        i = 0;
        pthread_mutex_lock(&base->run);
    }
   pthread_mutex_unlock(&base->run);
}

int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        printf("Wrong imput\n");
        return 0;
    }
    t_struct base;
    if (init_basic_var(av, &base) != 0)
        return (1);
    if (init_alloc(&base) != 0)
        return (1);
    if (init_fork(&base))
        return (1);
    init_philo(&base);
    if (init_thread(&base))
        return (1);
    is_dead(&base);
    do_join(&base);
    ft_cancel(&base);
}