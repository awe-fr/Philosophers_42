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
	int		number_of_philosopher;
	int		i;
	
	i = 0;
	number_of_philosopher = atoi(av[1]);
	base->philosophe = (pthread_t *)malloc(number_of_philosopher * sizeof(pthread_t));
        while (i < number_of_philosopher)
	{
                pthread_create(&(base->philosophe[i]), NULL, routine, base);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(1, "Wrong imput\n", 12);
		return (0);
	}
	t_struct	base;
	thread_init(av, &base);
}
