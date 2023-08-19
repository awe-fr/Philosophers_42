/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:03:36 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/19 03:03:38 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_header.h"

void	do_join(t_struct *base)
{
	int	i;

	i = 0;
	while (i < base->philo_number)
	{
		pthread_join(base->philosophe[i], NULL);
		i++;
	}
}

void	ft_cancel(t_struct *base)
{
	int	i;

	i = 0;
	while (i < base->philo_number)
	{
		pthread_mutex_destroy(&base->fork[i]);
		i++;
	}
	free(base->fork);
	free(base->perso);
	free(base->philosophe);
	pthread_mutex_destroy(&base->write);
	pthread_mutex_destroy(&base->run);
}

void	only_one(char **av)
{
	printf("0 | 1 | has taken a fork\n");
	usleep(ft_atoi(av[2]) * 1000);
	printf("%d | 1 | is dead\n", ft_atoi(av[2]));
}

int	main(int ac, char **av)
{
	t_struct	base;

	if (ac < 5 || ac > 6)
	{
		printf("Wrong imput\n");
		return (0);
	}
	if (init_basic_var(av, &base) != 0)
		return (1);
	if (ft_atoi(av[1]) == 1)
	{
		only_one(av);
		return (0);
	}
	if (init_alloc(&base) != 0)
		return (1);
	if (init_fork(&base))
		return (1);
	init_philo(&base);
	if (init_thread(&base))
		return (1);
	is_dead(&base);
	do_join(&base);
	ft_cancel(&base);
}
