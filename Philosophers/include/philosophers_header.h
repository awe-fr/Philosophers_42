/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_header.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:26:16 by srajaoui          #+#    #+#             */
/*   Updated: 2023/07/31 14:29:46 by srajaoui         ###   ########.fr       */
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
	pthread_t	*philosophe;
	pthread_mutex_t *fork;
	int	number_of_philosopher;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	how_much_eat;
}	t_struct;

int	ft_atoi(const char *str);

#endif
