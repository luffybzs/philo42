/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:06:46 by ayarab            #+#    #+#             */
/*   Updated: 2025/01/01 16:22:09 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

void	ft_last_eat(t_philo *philos)
{
	philos->last_eat = ft_time(philos->data);
}

int	ft_last_philos(t_philo *philos)
{
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(philos->r_fork);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 3), EXIT_FAILURE);
	ft_printf_philos(philos, FORK);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 3), EXIT_FAILURE);
	pthread_mutex_lock(&(philos->l_fork));
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 4), EXIT_FAILURE);
	ft_printf_philos(philos, FORK);
	ft_printf_philos(philos, EAT);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 4), EXIT_FAILURE);
	ft_sleep(philos, philos->data->time_to_eat);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 4), EXIT_FAILURE);
	philos->last_eat = ft_time(philos->data);
	ft_last_eat(philos);
	pthread_mutex_unlock(philos->r_fork);
	pthread_mutex_unlock(&(philos->l_fork));
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_eat_v1(t_philo *philos)
{
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&(philos->l_fork));
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 1), EXIT_FAILURE);
	ft_printf_philos(philos, FORK);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 2), EXIT_FAILURE);
	pthread_mutex_lock(philos->r_fork);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 2), EXIT_FAILURE);
	ft_printf_philos(philos, FORK);
	ft_printf_philos(philos, EAT);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 2), EXIT_FAILURE);
	ft_sleep(philos, philos->data->time_to_eat);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 2), EXIT_FAILURE);
	philos->last_eat = ft_time(philos->data);
	ft_last_eat(philos);
	pthread_mutex_unlock(&(philos->l_fork));
	pthread_mutex_unlock(philos->r_fork);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_eat(t_philo *philos)
{
	if (philos->id + 1 == philos->data->nb_philos)
	{
		if (ft_last_philos(philos) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		philos->nb_eat += 1;
	}
	else
	{
		if (ft_eat_v1(philos) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		philos->nb_eat += 1;
	}
	return (EXIT_SUCCESS);
}
