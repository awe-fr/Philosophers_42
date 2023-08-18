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
    do_join(&base);
    ft_cancel(&base);
}