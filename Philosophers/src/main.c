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

int	get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_death(t_struct *info, t_perso *perso, int time_to_pass)
{
	if (info->is_dead != -1)
		return (1);
	else if (((get_time() - info->time_start) - perso->last_meal) >= info->time_to_die)		
	{
		pthread_mutex_lock(&info->run);
		if (info->is_dead != -1)
			return (1);
		info->is_dead = perso->id;
		pthread_mutex_lock(&info->write);
		printf("%d    %d     is dead\n", get_time() - info->time_start, info->is_dead);
		pthread_mutex_unlock(&info->write);
		pthread_mutex_unlock(&info->run);
		return (1);
	}
	else if ((((get_time() - info->time_start) - perso->last_meal) + time_to_pass) >= info->time_to_die)
	{
		pthread_mutex_lock(&info->run);
		if (info->is_dead != -1)
			return (1);
		usleep(20 * 1000);
		info->is_dead = perso->id;
		pthread_mutex_lock(&info->write);
//		printf("%d, %d, %d\n", perso->last_meal, time_to_pass, info->time_to_die);
		printf("%d    %d     is dead\n", get_time() - info->time_start, info->is_dead);
		pthread_mutex_unlock(&info->write);
		pthread_mutex_unlock(&info->run);
		return (1);
	}
	return (0);
}

void	come_eat(t_struct *info, t_perso *perso)
{
	pthread_mutex_lock(&info->fork[perso->id - 1]);
	pthread_mutex_lock(&info->write);
	printf("%d    %d     has taken a fork\n", get_time() - info->time_start, perso->id);
	pthread_mutex_unlock(&info->write);
	if (perso->id == info->number_of_philosopher)
		pthread_mutex_lock(&info->fork[0]);
	else
		pthread_mutex_lock(&info->fork[perso->id]);
	pthread_mutex_lock(&info->write);
	printf("%d    %d     has taken a fork\n", get_time() - info->time_start, perso->id);
	pthread_mutex_unlock(&info->write);
	pthread_mutex_lock(&info->write);
	printf("%d    %d     is eating\n", get_time() - info->time_start, perso->id);
	pthread_mutex_unlock(&info->write);
	perso->last_meal = get_time() - info->time_start;
	if (check_death(info, perso, info->time_to_eat) == 1)
		return ;
	usleep(info->time_to_eat * 1000);
	pthread_mutex_unlock(&info->fork[perso->id - 1]);
	if (perso->id == info->number_of_philosopher)
		pthread_mutex_unlock(&info->fork[0]);
	else
		pthread_mutex_unlock(&info->fork[perso->id]);
	if (check_death(info, perso, info->time_to_sleep) == 1)
		return ;
	pthread_mutex_lock(&info->write);
	printf("%d    %d     is sleeping\n", get_time() - info->time_start, perso->id);
	pthread_mutex_unlock(&info->write);
	usleep(info->time_to_sleep * 1000);
}


void	*routine(void *base)
{
	t_struct *info;
	t_perso	 perso;
	int test;
	
	info = (t_struct *)base;
	perso.id = info->id + 1;
	perso.how_much_eat = info->how_much_eat;
	perso.last_meal = get_time() - info->time_start;
	while (perso.how_much_eat != 0)
	{
		if (check_death(info, &perso, 0) == 1)
			return NULL;
		come_eat(info, &perso);
		perso.how_much_eat -= 1;
		if (check_death(info, &perso, 0) == 1)
			return NULL;
		pthread_mutex_lock(&info->write);
		printf("%d    %d     is thinking\n", get_time() - info->time_start, perso.id);
		pthread_mutex_unlock(&info->write);
	}
	return NULL;
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
	pthread_mutex_init(&(base->run), NULL);
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
//	if ((ft_atoi(av[1]) == -2) || (ft_atoi(av[2]) == -2) || 
//	(ft_atoi(av[3]) == -2) || (ft_atoi(av[4]) == -2))
}

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
	pthread_mutex_destroy(&(base->write));
	pthread_mutex_destroy(&(base->run));
}

void	is_dead(t_struct *info)
{
	while (1)
	{
		if (info->is_dead != -1)
		{
			pthread_mutex_lock(&info->write);
			printf("%d    %d     is dead\n", get_time() - info->time_start, info->is_dead);
			pthread_mutex_unlock(&info->write);
			break;
		}
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
	basic_var_init(av, &base);
	mutex_init(av, &base);
	thread_init(av, &base);
//	is_dead(&base);
	do_the_join(av, &base);
	cancel_mutex(av, &base);
	return (0);
}
