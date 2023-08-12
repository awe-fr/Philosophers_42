/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 01:08:50 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/11 01:08:53 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_header.h"

void	*is_dead(void *perso)
{
	t_perso *philo;
	philo = perso;
	
	while(philo->is_dead == -1 && philo->how_much_eat != 0)
	{
		if(((get_time() - philo->time_start) - philo->last_meal) >= philo->time_to_die)
		{
			pthread_mutex_lock(&philo->run);
			if (philo->is_dead != -1)
			{
				pthread_mutex_unlock(&philo->run);
				return NULL;
			}
			philo->is_dead = philo->id;
			pthread_mutex_lock(&philo->write);
			printf("%d    %d     is dead\n", get_time() - philo->time_start, philo->is_dead);
			pthread_mutex_unlock(&philo->write);
			pthread_mutex_unlock(&philo->run);
			return NULL;
		}
	}
	return NULL;
}
