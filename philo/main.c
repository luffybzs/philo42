/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:31:38 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/23 18:51:43 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

int	ft_start_parsing(t_data *data);
int	ft_fill_data(int ac, char **av, t_data *data)
{
	data->ac = ac;
	data->av = av;
	if (ft_start_parsing(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_check_int(t_data *data, int flag)
{
	if (data->nb_philos < 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (flag == 1)
		if (data->nb_must_eat < 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_is_num(t_data *data)
{
	int	i;
	int	j;

	j = 1;
	while (data->av[j])
	{
		i = 0;
		if (data->av[j][i] == '+' || data->av[j][i] == '-')
			i++;
		while (data->av[j][i])
		{
			if (data->av[j][i] >= '0' && data->av[j][i] <= '9')
				i++;
			else
				return (EXIT_FAILURE);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int	ft_start_parsing(t_data *data)
{
	int	flag;

	if (ft_is_num(data) == EXIT_FAILURE)
		return (ft_putstr_fd("Error\nInvalid Character\n", 2), EXIT_FAILURE);
	flag = 0;
	data->nb_philos = ft_atoi_spe(data->av[1]);
	data->time_to_die = ft_atoi_spe(data->av[2]);
	data->time_to_eat = ft_atoi_spe(data->av[3]);
	data->time_to_sleep = ft_atoi_spe(data->av[4]);
	if (data->av[5])
	{
		data->nb_must_eat = ft_atoi_spe(data->av[5]);
		flag = 1;
	}
	else
		data->nb_must_eat = -1;
	if (ft_check_int(data, flag) == EXIT_FAILURE)
		return (ft_putstr_fd("Error\nValue\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
void *ft_routine(void *thread)
{

	t_philo *philo;

	philo = (t_philo *)thread;
	printf(" le id du philo %d\n", philo->id);
	// if (philo->id % 2 == 0)
	// 	//wait
	
	// while(1)
	// {
	// 	if (!ft_dead(philo))
	// 		break;
	// 	if (!ft_eat(philo))
	// 		break;
	// 	if (!ft_sleep(philo))
	// 		break;
	// 	if (!ft_think(philo))
	// 		break;
	// 	if (!ft_repu(philo))
	// 		break;
	// }
	return 0;
}

int ft_monitor(t_philo *philos, t_data *data)
{
	int i = 0;
	while(i < data->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, &ft_routine, &philos[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
/*
long ft_custom_usleep()
{
	while()
	{
		dead(dead);
		usleep(10);
	}

}
*/

int ft_set_table(t_data *data, t_philo **philos)
{
	int i;
	t_philo *tab;
	
	tab = malloc(sizeof(t_philo) * data->nb_philos);
	if (tab == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while(i < data->nb_philos)
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
	t_data data;
	t_philo *philos;
	
	if (ac != 6 && ac != 5)
		return (ft_putstr_fd("Error\nNot Or Too Many Arguments\n", 2),
			 EXIT_FAILURE);
	if (ft_fill_data(ac, av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_set_table(&data, &philos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_monitor(philos, &data);
	sleep(5);
	return (EXIT_SUCCESS);
}
