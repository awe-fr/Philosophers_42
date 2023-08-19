/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:02:47 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/19 03:02:49 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_header.h"

void	death_action(t_struct *base)
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

void	is_dead(t_struct *base)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&base->run);
	while (base->is_okay > 0 && base->is_dead == -1)
	{
		pthread_mutex_unlock(&base->run);
		while (i < base->philo_number)
		{
			pthread_mutex_lock(&base->run);
			if ((((get_time() - base->time_start) - base->perso[i].last_meal) \
			>= base->time_to_die) && base->perso[i].how_much_eat != 0)
			{
				death_action(base);
				return ;
			}
			else if (base->perso[i].how_much_eat == 0)
				base->is_okay--;
			pthread_mutex_unlock(&base->run);
			i++;
		}
		i = 0;
		pthread_mutex_lock(&base->run);
	}
	pthread_mutex_unlock(&base->run);
}
