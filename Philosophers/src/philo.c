/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 01:09:12 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/12 22:13:16 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_header.h"

void	go_sleep(t_perso *perso)
{
	print(get_time(), perso->id, "is sleeping", perso);
	usleep(perso->time_to_sleep * 1000);
	print(get_time(), perso->id, "is thinking", perso);
}

void	come_eat(t_perso *perso)
{
	print(get_time(), perso->id, "is eating", perso);
	perso->last_meal = get_time() - perso->time_start;
	usleep(perso->time_to_eat * 1000);
}

void	take_fork(t_perso *perso)
{
	pthread_mutex_lock(&perso->base->fork[perso->f_fork]);
	print(get_time(), perso->id, "has taken a fork", perso);
	pthread_mutex_lock(&perso->base->fork[perso->s_fork]);
	print(get_time(), perso->id, "has taken a fork", perso);
	come_eat(perso);
	pthread_mutex_unlock(&perso->base->fork[perso->s_fork]);
	pthread_mutex_unlock(&perso->base->fork[perso->f_fork]);
}

void	what_fork(t_perso *perso)
{
	if (perso->id % 2 == 0)
	{
		perso->f_fork = perso->id - 1;
		if (perso->id == perso->number_of_philosopher)
			perso->s_fork = 0;
		else
			perso->s_fork = perso->id; 
	}
	else
	{
		if (perso->id == 1)
			perso->f_fork = perso->number_of_philosopher -1;
		else 
			perso->f_fork = perso->id - 2;
		perso->s_fork = perso->id - 1;
	}
}

void	*routine(void *per)
{
	t_perso *perso;
	
	perso = (t_perso *)per;
//	pthread_create(&(perso.philo), NULL, is_dead, &perso);
	what_fork(perso);
	while(perso->how_much_eat !=  0)
	{
		if (perso->base->is_dead != -1)
			break;
		take_fork(perso);
		perso->how_much_eat -= 1;
		go_sleep(perso);	
	}
	pthread_join(perso->philo, NULL);
	return NULL;
}

void	only_one(t_perso *perso)
{
	printf("%d    %d     %s\n", 0, 1, "has taken a fork");
	usleep(perso[0].time_to_die * 1000);
	printf("%d    %d     %s\n", perso[0].time_to_die, 1, "id dead");
}
