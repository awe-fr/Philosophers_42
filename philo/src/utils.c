/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:04:02 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/19 03:04:03 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_header.h"

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

void	print(int id, char *to_print, t_perso *perso)
{
	long int	rtime;

	pthread_mutex_lock(&perso->base->run);
	pthread_mutex_lock(&perso->base->write);
	rtime = get_time() - perso->time_start;
	if (perso->base->is_dead == -1)
		printf("%ld | %d | %s\n", rtime, id, to_print);
	pthread_mutex_unlock(&perso->base->write);
	pthread_mutex_unlock(&perso->base->run);
}
