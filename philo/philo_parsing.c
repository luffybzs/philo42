/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:33:06 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/26 17:27:22 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

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
	if (data->nb_philos <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
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
void	ft_pthread_join_all(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
