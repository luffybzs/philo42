/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:31:38 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/31 18:24:05 by ayarab           ###   ########.fr       */
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
long	ft_time(t_data *data)
{
	struct timeval	now;
	long long		now_time;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	now_time = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return (now_time - data->start_time);
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
		{
			philos[i].launch = false;
			return (EXIT_FAILURE);
		}
		philos[i].launch = true;
		i++;
	}
	return (EXIT_SUCCESS);
}

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
	t_philo	*philos = {0};
	if (ac != 6 && ac != 5)
		return (ft_putstr_fd("Error\nNot Or Too Many Arguments\n", 2),
			EXIT_FAILURE);
	if (ft_fill_data(ac, av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_set_table(&data, &philos) == EXIT_FAILURE)
		return (free(philos), EXIT_FAILURE);
	if (ft_create_thread_and_mutex(philos, &data) == EXIT_FAILURE)
		return (free(philos), EXIT_FAILURE);
	ft_pthread_join_all(philos);
	return (free(philos), EXIT_SUCCESS);
}
