/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:33:00 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/31 18:23:26 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>

# define EAT "is eating"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define DIED "has died"
# define THINK "is thinking"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
typedef struct s_data
{
	char			**av;
	int				ac;
	long long		start_time;
	long			nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	bool			is_dead;
	pthread_mutex_t	print;
	pthread_mutex_t	died;
}					t_data;

typedef struct s_philo
{
	int				id;
	bool			launch;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	unsigned int	last_eat;

}					t_philo;

void				ft_unlock(t_philo *philos, int value);
int					ft_set_table(t_data *data, t_philo **philos);
int					ft_create_thread_and_mutex(t_philo *philos, t_data *data);
bool				ft_status_died(t_philo *philo);
long				ft_time(t_data *data);
int					ft_philos_sleep(t_philo *philos);
int					ft_eat(t_philo *philos);
void				*ft_routine(void *thread);
int					ft_think(t_philo *philo);
int					ft_dead(t_philo *philos);
int					ft_sleep(t_philo *philos, long time);
int					ft_printf_philos(t_philo *philos, char *str);
void				ft_pthread_join_all(t_philo *philos);
int					ft_fill_data(int ac, char **av, t_data *data);
int					ft_start_parsing(t_data *data);
long				ft_atoi_spe(char *str);
void				ft_putstr_fd(char *str, int fd);
int					ft_check_int(t_data *data, int flag);
int					ft_is_num(t_data *data);
int					ft_start_parsing(t_data *data);
#endif