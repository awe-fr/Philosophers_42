/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_header.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:26:16 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/11 01:03:16 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_HEADER_H
# define PHILOSOPHERS_HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_perso
{
	pthread_t       philo;
	pthread_mutex_t write;
	pthread_mutex_t run;
	int	id;
	int	last_meal;
	int	how_much_eat;
	int	time_start;
	int	is_dead;
	int	time_to_die;
}	t_perso;

typedef struct s_struct
{
	pthread_t	*philosophe;
	pthread_mutex_t *fork;
	pthread_mutex_t write;
	int	number_of_philosopher;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	how_much_eat;
	int	id;
	int	time_start;
	int	is_dead;
}	t_struct;


int	ft_atoi(const char *str);
void	basic_var_init(char **av, t_struct *base);
void	mutex_init(char **av, t_struct *base);
void	thread_init(char **av, t_struct *base);
void	*routine(void *base);
void	take_fork(t_struct *info, t_perso *perso);
void	come_eat(t_struct *info, t_perso *perso);
void	go_sleep(t_struct *info, t_perso *perso);
void	perso_init(t_perso *perso, t_struct *info);
void	basic_var_init(char **av, t_struct *base);
void	print(int time, int id, char *to_print, t_struct *info);
int	get_time(void);
void	do_the_join(char **av, t_struct *base);
void	cancel_mutex(char **av, t_struct *base);

#endif
