/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:31:38 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/29 04:09:24 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

bool	ft_status_died(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->died);
	status = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->died);
	return (status);
}
long ft_time(t_data *data)
{
	struct timeval now;
	long long now_time;
	
	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	now_time = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return(now_time - data->start_time);
}

int ft_printf_philos(t_philo *philos, char *str)
{
	pthread_mutex_lock(&philos->data->print);
	printf("%ld %d %s\n",ft_time(philos->data), philos->id, str);
	pthread_mutex_unlock(&philos->data->print);
	return (EXIT_SUCCESS);
}

int ft_sleep(t_philo *philos, long time)
{
	long start;
	
	start = ft_time(philos->data);
	while ((ft_time(philos->data) - start) < time)  
	{
		if (ft_status_died(philos) == true)
			break;
		usleep(10);
	}
	return (EXIT_SUCCESS);
}

int ft_eat(t_philo *philos)
{
	
	pthread_mutex_lock(philos->r_fork);
	ft_printf_philos(philos, FORK); 
	pthread_mutex_lock(&philos->l_fork);
	ft_printf_philos(philos, FORK);
	ft_printf_philos(philos, EAT);
	ft_sleep(philos, philos->data->time_to_eat); 
	pthread_mutex_unlock(philos->r_fork);
	pthread_mutex_unlock(&philos->l_fork);
	return (EXIT_SUCCESS);
}



void	*ft_routine(void *thread)
{
	t_philo	*philo;
	philo = (t_philo *)thread;
	//long time;
	//time = ft_time(philo->data);
	//printf("le id : %d and time = %ld\n", philo->id, time);
	if (philo->id % 2 == 0)
			ft_sleep(philo, 2);
	 while(1)
	 {
		//if (!ft_dead(philo))
	 	//	break ;
	 	if (!ft_eat(philo))
	 		break ;
	 	//if (!ft_sleep(philo))
	 	//	break ;
	 	//if (!ft_think(philo))
	 	//	break ;
	 	//if (!ft_repu(philo))
	 	//	break ;
	} 
	return (0);
}

int	ft_create_thread_and_mutex(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->died, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->is_dead = false;
	while (i < data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &ft_routine,
				&philos[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
long	ft_custom_usleep(void)
{
	while()
	{
		dead(dead);
		usleep(10);
	}
}
*/

int	ft_set_table(t_data *data, t_philo **philos)
{
	int		i;
	t_philo	*tab;

	tab = malloc(sizeof(t_philo) * data->nb_philos);
	if (tab == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_philos)
	{
		tab[i].id = i + 1;
		tab[i].data = data;
		pthread_mutex_init(&tab[i].l_fork, NULL);
		tab[i].r_fork = &tab[(i + 1) % data->nb_philos].l_fork;
		i++;
	}
	*philos = tab;
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (ac != 6 && ac != 5)
		return (ft_putstr_fd("Error\nNot Or Too Many Arguments\n", 2),
			EXIT_FAILURE);
	if (ft_fill_data(ac, av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_set_table(&data, &philos) == EXIT_FAILURE)
		return (free(philos), EXIT_FAILURE);
	if (ft_create_thread_and_mutex(philos, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//ft_monitor(philos, &data);
	ft_pthread_join_all(philos);
	return (free(philos), EXIT_SUCCESS);
}
