/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:31:38 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/26 17:34:01 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

void	*ft_routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	printf(" le id du philo %d\n", philo->id);
	// if (philo->id % 2 == 0)
	// 	//wait
	// while(1)
	// {
	// 	if (!ft_dead(philo))
	// 		break ;
	// 	if (!ft_eat(philo))
	// 		break ;
	// 	if (!ft_sleep(philo))
	// 		break ;
	// 	if (!ft_think(philo))
	// 		break ;
	// 	if (!ft_repu(philo))
	// 		break ;
	// }
	return (0);
}

int	ft_monitor(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, &ft_routine, &philos[i]);
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
		return (EXIT_FAILURE);
	ft_monitor(philos, &data);
	ft_pthread_join_all(philos);
	free(philos);
	return (EXIT_SUCCESS);
}
