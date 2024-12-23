/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:33:00 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/23 18:52:55 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <limits.h>

#define EAT "is eating"
#define FORK "has taken a fork"
#define SLEEP "is sleeping"
#define DIED "has died"
#define THINK "is thinking"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>




typedef struct s_data
{
	char **av;
	int ac;
	long nb_philos;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nb_must_eat;
	pthread_mutex_t  print;
	pthread_mutex_t  died;
}   t_data;

typedef struct s_philo
{
	int				id;
	pthread_t       thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	
}  t_philo;



long ft_atoi_spe(char *str);
void ft_putstr_fd(char *str, int fd);

#endif