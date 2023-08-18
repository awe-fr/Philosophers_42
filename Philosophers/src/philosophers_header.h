#ifndef PHILOSOPHERS_HEADER_H
# define PHILOSOPHERS_HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>

struct s_struct;

typedef struct s_perso
{
	int			philo_number;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			how_much_eat;
	long int	last_meal;
	long int	time_start;
	int			id;
	int			f_fork;
	int			s_fork;
	struct s_struct *base;
}	t_perso;

typedef struct s_struct
{
	pthread_t       *philosophe;
	pthread_mutex_t *fork;
	pthread_mutex_t write;
	pthread_mutex_t run;
	int			philo_number;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			how_much_eat;
	long int	time_start;
	int			is_dead;
	int			is_okay;
    t_perso *perso;
}	t_struct;

int	get_time(void);
int	ft_atoi(const char *str);
int init_basic_var(char **av, t_struct *base);
int    init_alloc(t_struct *base);
void    init_philo(t_struct *base);
int init_fork(t_struct *base);
int    init_thread(t_struct *base);
void    do_join(t_struct *base);
void *routine(void *per);
void    come_eat(t_perso *perso);
void	go_sleep(t_perso *perso);
void    take_fork(t_perso *perso);
void    print(int id, char *to_print, t_perso *perso);

#endif