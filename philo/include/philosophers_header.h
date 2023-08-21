/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_header.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:03:55 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/21 13:27:47 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_HEADER_H
# define PHILOSOPHERS_HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

struct	s_struct;

typedef struct s_perso
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				how_much_eat;
	int				id;
	int				right_fork;
	int				left_fork;
	long int		last_meal;
	long int		time_start;
	struct s_struct	*base;
}	t_perso;

typedef struct s_struct
{
	pthread_t		*philosophe;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	run;
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				how_much_eat;
	int				is_dead;
	int				is_okay;
	long int		time_start;
	t_perso			*perso;
}	t_struct;

int		get_time(void);
int		ft_atoi(const char *str);
int		init_fork(t_struct *base);
int		init_alloc(t_struct *base);
int		init_thread(t_struct *base);
int		init_basic_var(char **av, t_struct *base);
void	only_one(char **av);
void	is_dead(t_struct *base);
void	do_join(t_struct *base);
void	come_eat(t_perso *perso);
void	go_sleep(t_perso *perso);
void	take_fork(t_perso *perso);
void	ft_cancel(t_struct *base);
void	init_philo(t_struct *base);
void	place_fork(t_struct *base);
void	death_action(t_struct *base);
void	print(int id, char *to_print, t_perso *perso);
void	*routine(void *per);

#endif
