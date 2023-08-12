/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 01:09:03 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/11 01:09:05 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_header.h"

void	perso_init(t_perso *perso, t_struct *info)
{
	perso->id = info->id + 1;
	perso->how_much_eat = info->how_much_eat;
	perso->last_meal = get_time() - info->time_start;
	perso->is_dead = -1;
	perso->time_to_die = info->time_to_die;
	perso->time_start = info->time_start;
}

void	basic_var_init(char **av, t_struct *base)
{
	base->number_of_philosopher = ft_atoi(av[1]);
	base->time_to_die = ft_atoi(av[2]);
	base->time_to_eat = ft_atoi(av[3]);
	base->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		base->how_much_eat = ft_atoi(av[5]);
	else
		base->how_much_eat = -1;
	base->is_dead = -1;
}

void	mutex_init(char **av, t_struct *base)
{
	int		i;
	
	i = 0;
	base->fork = (pthread_mutex_t *)malloc(base->number_of_philosopher * sizeof(pthread_mutex_t));
	while (i < base->number_of_philosopher)
	{
		pthread_mutex_init(&(base->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(base->write), NULL);
}

void	thread_init(char **av, t_struct *base)
{
	int		i;
	
	i = 0;
	base->time_start = get_time();
	base->philosophe = (pthread_t *)malloc(base->number_of_philosopher * sizeof(pthread_t));
	while (i < base->number_of_philosopher)
	{
		base->id = i;
		pthread_create(&(base->philosophe[i]), NULL, routine, base);
		usleep(5 * base->number_of_philosopher);
		i++;
	}
}
