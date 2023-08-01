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

#include "../include/philosophers_header.h"

void	*routine(void *base)
{

}

void	thread_init(char **av, t_struct *base)
{
	int		i;
	
	i = 0;
	base->philosophe = (pthread_t *)malloc(base->number_of_philosopher * sizeof(pthread_t));
        while (i < base->number_of_philosopher)
	{
                pthread_create(&(base->philosophe[i]), NULL, routine, base);
		i++;
	}
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
}

void	basic_var_init(char **av, t_struct *base)
{
	base->number_of_philosopher = ft_atoi(av[1]);
	base->time_to_die = ft_atoi(av[2]);
	base->time_to_eat = ft_atoi(av[3]);
	base->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		base->how_much_eat = ft_atoi(av[5]);
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
	mutex_init(av, &base);
	thread_init(av, &base);
}	
