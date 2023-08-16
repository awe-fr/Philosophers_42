/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:25:30 by srajaoui          #+#    #+#             */
/*   Updated: 2023/07/31 18:12:25 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_header.h"

void	do_the_join(t_struct *base, t_perso *perso)
{
	int i;
	
	i = 0;
	while (i < perso[i].number_of_philosopher)
	{
		pthread_join(perso[i].philosophe, NULL);
		i++;
	}
}

void	cancel_mutex(t_struct *base, t_perso *perso)
{
	int i;
	
	i = 0;
	while (i < perso->number_of_philosopher)
	{
		pthread_mutex_destroy(&(base->fork[i]));
		i++;
	}
	free(base->fork);
	pthread_mutex_destroy(&(base->write));
	pthread_mutex_destroy(&(base->run));
	free(perso);
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(1, "Wrong imput\n", 12);
		return (0);
	}
	t_struct	base;
	t_perso	*perso;
	perso = basic_var_init(av, &base);
	if (perso[0].number_of_philosopher == 1)
	{
		only_one(perso);
		free(perso);
		return (0);
	}
	if (is_number(perso) == -1)
	{
		write(1, "Wrong imput\n", 12);
		return (0);
	}
	mutex_init(&base, perso);
	thread_init(perso, &base);
	do_the_join(&base, perso);
	cancel_mutex(&base, perso);
	return (0);
}
