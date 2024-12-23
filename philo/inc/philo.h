/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:33:00 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/23 02:42:31 by ayarab           ###   ########.fr       */
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


typedef struct s_philo
{
	int		id;
	
	t_philo	*next;
	
	t_data *data;
	
}  t_philo;


typedef struct s_data
{
	char **av;
	int ac;
	long nop;
	long ttd;
	long tte;
	long tts;
	long nofep;
	pthread_mutex_t  print;
	pthread_mutex_t  fork;
	pthread_mutex_t  ate;
	pthread_mutex_t  died;
	t_philo    *head;
	
}   t_data;



t_philo				*ft_lstnew(void *content);

t_philo				*ft_lstlast(t_philo *lst);


void				ft_lstadd_back(t_philo **lst, t_philo *new);


void				ft_lstclear(t_philo **lst, void (*del)(void *));



long ft_atoi_spe(char *str);
void ft_putstr_fd(char *str, int fd);

#endif