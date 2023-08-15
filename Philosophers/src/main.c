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

void	do_the_join(char **av, t_struct *base)
{
	int i;
	
	i = 0;
	while (i < base->number_of_philosopher)
	{
		pthread_join(base->philosophe[i], NULL);
		i++;
	}
}

void	cancel_mutex(char **av, t_struct *base)
{
	int i;
	
	i = 0;
	while (i < base->number_of_philosopher)
	{
		pthread_mutex_destroy(&(base->fork[i]));
		i++;
	}
	free(base->fork);
	free(base->philosophe);
	pthread_mutex_destroy(&(base->write));
	pthread_mutex_destroy(&(base->run));
	pthread_mutex_destroy(&(base->assign));
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(1, "Wrong imput\n", 12);
		return (0);
	}
	t_struct	base;
	basic_var_init(av, &base);
	if (base.number_of_philosopher == 1)
	{
		only_one(&base);
		return (0);
	}
	if (is_number(&base) == -1)
	{
		write(1, "Wrong imput\n", 12);
		return (0);
	}
	mutex_init(av, &base);
	thread_init(av, &base);
	do_the_join(av, &base);
	cancel_mutex(av, &base);
	return (0);
}
