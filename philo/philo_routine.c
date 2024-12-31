/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:10:35 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/31 21:50:34 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

int	ft_philos_sleep(t_philo *philos)
{
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_printf_philos(philos, SLEEP);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_sleep(philos, philos->data->time_to_sleep);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_sleep(t_philo *philos, long time)
{
	long	start;

	start = ft_time(philos->data);
	while ((ft_time(philos->data) - start) < time)
	{
		if (ft_status_died(philos) == true)
			break ;
		usleep(10);
	}
	return (EXIT_SUCCESS);
}
void	ft_last_eat(t_philo *philos)
{
	pthread_mutex_lock(&philos->lse);
	philos->last_eat = ft_time(philos->data);
	pthread_mutex_unlock(&philos->lse);
}

int	ft_eat(t_philo *philos)
{
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philos->id + 1 == philos->data->nb_philos)
	{
		pthread_mutex_lock(philos->r_fork);
		pthread_mutex_lock(&(philos->l_fork));
	}
	else
	{
		pthread_mutex_lock(&(philos->l_fork));
		if (ft_dead(philos) == EXIT_FAILURE)
			return (ft_unlock(philos, 1), EXIT_FAILURE);
		ft_printf_philos(philos, FORK);
		if (ft_dead(philos) == EXIT_FAILURE)
			return (ft_unlock(philos, 1), EXIT_FAILURE);
		pthread_mutex_lock(philos->r_fork);
	}
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 2), EXIT_FAILURE);
	ft_printf_philos(philos, FORK);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (ft_unlock(philos, 2), EXIT_FAILURE);
	ft_printf_philos(philos, EAT);
	ft_sleep(philos, philos->data->time_to_eat);
	 if (ft_dead(philos) == EXIT_FAILURE)
	 	return (ft_unlock(philos, 2), EXIT_FAILURE);
	if (philos->id + 1 == philos->data->nb_philos)
	{
		pthread_mutex_unlock(philos->r_fork);
		pthread_mutex_unlock(&(philos->l_fork));
	}
	else
	{
		pthread_mutex_unlock(&(philos->l_fork));
		pthread_mutex_unlock(philos->r_fork);
	}
	ft_last_eat(philos);
	if (ft_dead(philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_dead(t_philo *philos)
{
	long	start;
	long	last_meal_time;

	if (ft_status_died(philos) == true)
		return (EXIT_FAILURE);
	start = ft_time(philos->data);
	last_meal_time = philos->last_eat;
	if ((start - last_meal_time) >= philos->data->time_to_die)
	{
		pthread_mutex_lock(&philos->data->died);
		if (philos->data->is_dead == false)
		{
			ft_printf_philos(philos, DIED);
			philos->data->is_dead = true;
		}
		pthread_mutex_unlock(&philos->data->died);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
void	*ft_routine(void *thread)
{
	t_philo *philo;

	philo = (t_philo *)thread;
	if (ft_printf_philos(philo, THINK) == EXIT_FAILURE)
		return (0);
	if (philo->id % 2 == 0)
		ft_sleep(philo, 2);
	while (1)
	{
		if (ft_dead(philo) == EXIT_FAILURE)
			break ;
		if (ft_eat(philo) == EXIT_FAILURE)
			break ;
		// if (philo->number_of_meal == philo->data->nb_must_eat)
		// printf("philo[%d], ate %d meal", philo->id, philo->number_of_meal);
		// break ; //ajouter dans la structure philo un compteur de repas
		if (ft_philos_sleep(philo) == EXIT_FAILURE)
			break ;
		if (ft_think(philo) == EXIT_FAILURE)
			break ;
	}
	return (0);
}