/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_header.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:26:16 by srajaoui          #+#    #+#             */
/*   Updated: 2023/08/13 06:46:23 by srajaoui         ###   ########.fr       */
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


typedef struct s_struct
{
//	pthread_t	*philosophe;
	pthread_mutex_t *fork;
	pthread_mutex_t write;
	pthread_mutex_t run;
	long int	time_start;
	int	is_dead;
}	t_struct;

typedef struct s_perso
{
	pthread_t       death;
	pthread_t       philosophe;
	int	number_of_philosopher;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	how_much_eat;
	long int	last_meal;
	long int	time_start;
	int	*is_dead;
	int	id;
	int f_fork;
	int s_fork;
	t_struct *base;
}	t_perso;

int	ft_atoi(const char *str);
t_perso	*basic_var_init(char **av, t_struct *base);
void	mutex_init(t_struct *base, t_perso *perso);
void	thread_init(t_perso *perso, t_struct *base);
void	*routine(void *perso);
void	take_fork(t_perso *perso);
void	come_eat(t_perso *perso);
void	go_sleep(t_perso *perso);
//void	perso_init(t_perso *perso, t_struct *info);
void	print(int time, int id, char *to_print, t_perso *perso);
int	get_time(void);
void	do_the_join(t_struct *base, t_perso *perso);
void	cancel_mutex(t_struct *base, t_perso *perso);
//void	*is_dead(void *perso);
void	only_one(t_perso *perso);
int	is_number(t_perso *perso);

#endif
