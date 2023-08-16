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

// void	perso_init(t_perso *perso, t_struct *info)
// {
// 	perso->id = info->id + 1;
// 	perso->how_much_eat = info->how_much_eat;
// 	perso->last_meal = get_time() - info->time_start;
// 	perso->is_dead = &(info->is_dead);
// 	perso->time_to_die = info->time_to_die;
// 	perso->time_start = info->time_start;
// 	perso->number_of_philosopher = info->number_of_philosopher;
// 	perso->time_to_eat = info->time_to_eat;
// 	perso->time_to_sleep = info->time_to_sleep;
// }

t_perso	*basic_var_init(char **av, t_struct *base)
{
	t_perso *perso;
	int i;

	i = 0;
	perso = (t_perso *)malloc(ft_atoi(av[1]) * sizeof(t_perso));
	base->is_dead = -1;
	base->time_start = get_time();
	while (i < ft_atoi(av[1]))
	{
		perso[i].number_of_philosopher = ft_atoi(av[1]);
		perso[i].time_to_die = ft_atoi(av[2]);
		perso[i].time_to_eat = ft_atoi(av[3]);
		perso[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			perso[i].how_much_eat = ft_atoi(av[5]);
		else
			perso[i].how_much_eat = -1;
		i++;
		perso[i].is_dead = &(base->is_dead);
		perso[i].time_start = base->time_start;
		perso[i].last_meal = perso[i].time_start;
		perso[i].id = i + 1;
		perso[i].base = base;
	}
	return (perso);
}

void	mutex_init(t_struct *base, t_perso *perso)
{
	int		i;
	
	i = 0;
	base->fork = (pthread_mutex_t *)malloc(perso[0].number_of_philosopher * sizeof(pthread_mutex_t));
	while (i < perso[0].number_of_philosopher)
	{
		pthread_mutex_init(&(base->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(base->write), NULL);
	pthread_mutex_init(&(base->run), NULL);
}

void	thread_init(t_perso *perso, t_struct *base)
{
	int		i;

	i = 0;
	//base->time_start = get_time();
	//base->philosophe = (pthread_t *)malloc(perso[0].number_of_philosopher * sizeof(pthread_t));
	//if (base->philosophe == NULL)
	//	return ;
	while (i < perso[0].number_of_philosopher)
	{
		if (pthread_create(&perso[i].philosophe, NULL, routine, &perso[i]) != 0)
			return ;
		usleep(10);
		i++;
	}
}
