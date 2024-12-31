/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:18:29 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/31 21:23:19 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

int	ft_think(t_philo *philo)
{
	if (ft_dead(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_printf_philos(philo, THINK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_dead(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo->data->nb_philos % 2 == 0)
		ft_sleep(philo, philo->data->time_to_eat - philo->data->time_to_sleep);
	else
		ft_sleep(philo, (2 * philo->data->time_to_eat)
			- philo->data->time_to_sleep);
	return (EXIT_SUCCESS);
}

void	ft_unlock(t_philo *philos, int value)
{
	if (value == 1)
		pthread_mutex_unlock(&(philos->l_fork));
	else if  (value == 2)
	{
		pthread_mutex_unlock(philos->r_fork);
		pthread_mutex_unlock(&(philos->l_fork));
	}
}

int	ft_printf_philos(t_philo *philos, char *str)
{
	pthread_mutex_lock(&(philos->data->print));
	printf("%ld %d %s\n", ft_time(philos->data), philos->id, str);
	pthread_mutex_unlock(&(philos->data->print));
	return (EXIT_SUCCESS);
}
