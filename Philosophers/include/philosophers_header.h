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
}	t_struct;

#endif
