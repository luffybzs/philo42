/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab < ayarab@student.42.fr >            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:31:38 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/19 14:15:12 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void fill_data(int ac, char **av , t_data *data)
{
	data->ac = ac;
	data->av = av;
}
int ft_check_int(t_data *data, int flag)
{
	if (data->nop == 2147483648 || data->ttd == 2147483648 
		|| data->tte == 2147483648 || data->tts == 2147483648)
		return (EXIT_FAILURE);
	if (data->nop < 0 || data->ttd < 0 
		|| data->tte < 0 || data->tts < 0)
		return (EXIT_FAILURE);
	if (flag == 1)
		if (data->nofep == 2147483648 || data->nofep < 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
int ft_is_num(t_data *data)
{
	int i;
	int j;

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

int ft_start_parsing(t_data *data)
{
	int flag;

	if (ft_is_num(data) == EXIT_FAILURE)
		return (ft_putstr_fd("Error\nInvalid Character\n", 2) ,EXIT_FAILURE);
	flag = 0;
	data->nop = ft_atoi_spe(data->av[1]);
	data->ttd = ft_atoi_spe(data->av[2]);
	data->tte = ft_atoi_spe(data->av[3]);
	data->tts = ft_atoi_spe(data->av[4]);
	if (data->av[5])
	{
		data->nofep = ft_atoi_spe(data->av[5]);
		flag = 1;	
	}
	if (ft_check_int(data, flag) == EXIT_FAILURE)
		return (ft_putstr_fd("Error\nValue\n",2),EXIT_FAILURE);
	return (EXIT_SUCCESS);
}



int main(int ac, char **av)
{
	t_data data;
	
	if (ac > 6 || ac < 5)
		return (ft_putstr_fd("Error\nNot Or Too Many Arguments\n", 2) ,EXIT_FAILURE);
	fill_data(ac, av, &data);
	if (ft_start_parsing(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}