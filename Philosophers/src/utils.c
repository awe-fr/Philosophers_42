#include "philosophers_header.h"

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

void	print(int time, int id, char *to_print, t_struct *info)
{
	pthread_mutex_lock(&info->write);
	int	rtime;
	
	rtime = time - info->time_start;
	if (info->is_dead == -1)
		printf("%d    %d     %s\n", rtime, id, to_print);
	pthread_mutex_unlock(&info->write);
}

int	get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_number(t_struct *base)
{
	if (base->number_of_philosopher <= 0)
		return (-1);
	if (base->time_to_die <= 0)
		return (-1);
	if (base->time_to_eat <= 0)
		return (-1);
	if (base->time_to_sleep <= 0)
		return (-1);
	if (base->how_much_eat == 0 || base->how_much_eat <= -2)
		return (-1);
	return (0);
}
