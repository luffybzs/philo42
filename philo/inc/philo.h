/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:33:00 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/21 20:47:19 by ayarab           ###   ########.fr       */
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


// typedef struct s_factory
// {
	
// 	t_factory *next;
// }	t_factory;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;


// typedef struct s_factory_head
// {
// 	t_factory *head;
// } t_factory_head;




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
}   t_data;



t_list				*ft_lstnew(void *content);

t_list				*ft_lstlast(t_list *lst);


void				ft_lstadd_back(t_list **lst, t_list *new);


void				ft_lstclear(t_list **lst, void (*del)(void *));



long ft_atoi_spe(char *str);
void ft_putstr_fd(char *str, int fd);

#endif