#include "philosophers_header.h"

int	get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	result;

	i = 0;
	neg = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * neg);
}


void    print(int id, char *to_print, t_perso *perso)
{
    pthread_mutex_lock(&perso->base->write);
    long int rtime;

    //pthread_mutex_lock(&perso->base->run);
    rtime = get_time() - perso->time_start;
    if (perso->base->is_dead == -1)
        printf("%ld | %d | %s\n", rtime, id, to_print);
  //  pthread_mutex_unlock(&perso->base->run);
    pthread_mutex_unlock(&perso->base->write);
}