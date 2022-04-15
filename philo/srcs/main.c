/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 02:55:02 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/14 02:43:52 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	atoi_mod(int *value, char *str)
{
	int			i;
	int			nb;

	if (!check_arg(str))
		return (0);
	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb <= 0)
		return (0);
	*value = nb;
	return (1);
}

static int	init_data(t_data *data, char **av)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (0);
	if (!atoi_mod(&data->nb_philo, av[1]))
		return (0);
	if (!atoi_mod(&data->time_die, av[2]))
		return (0);
	if (!atoi_mod(&data->time_eat, av[3]))
		return (0);
	if (!atoi_mod(&data->time_sleep, av[4]))
		return (0);
	if (!av[5])
		data->round = -1;
	else
		if (!atoi_mod(&data->round, av[5]))
			return (0);
	data->philos = NULL;
	data->death_status = 1;
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1 || ac > 6 || !init_data(&data, av))
	{
		printf("Error\n");
		return (-1);
	}
	if (!init_dinner(&data))
	{
		clean_up(&data);
		return (-2);
	}
	return (run(&data));
}
