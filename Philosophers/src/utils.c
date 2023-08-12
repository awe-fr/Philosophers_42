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
			return (-2);
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
	if (info->is_dead != -1)
	{
		pthread_mutex_unlock(&info->write);
		return ;
	}
	printf("%d    %d     %s\n", time - info->time_start, id, to_print);
	pthread_mutex_unlock(&info->write);
}

int	get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
