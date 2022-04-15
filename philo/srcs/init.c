/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:25:36 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/14 02:22:55 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	add_philo(t_lst **lst, void *content)
{
	t_lst	*ptr;
	t_lst	*new;

	if (!content)
	{
		new->content = NULL;
		new->next = NULL;
		return (0);
	}	
	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	if (*lst)
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*lst = new;
	return (1);
}

static void	init_philo_stat(t_data *data, t_philo *new_philo)
{
	new_philo->fork = 0;
	new_philo->eat_status = data->round;
	new_philo->data = data;
	add_philo(&data->philos, new_philo);
}

static int	creat_new_philo(t_data *data, int index)
{
	int		ret;
	t_philo	*new_philo;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		return (0);
	new_philo->index = index;
	if (pthread_mutex_init(&(new_philo)->fork_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(new_philo)->last_eat_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(new_philo)->fork_mutex);
		return (0);
	}
	if (pthread_mutex_init(&(new_philo)->eat_status_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(new_philo)->fork_mutex);
		pthread_mutex_destroy(&(new_philo)->last_eat_mutex);
		add_philo(&data->philos, NULL);
		return (0);
	}
	init_philo_stat(data, new_philo);
	return (1);
}

int	init_mutex(t_data	*data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		return (0);
	}
	return (1);
}

int	init_dinner(t_data *data)
{
	int		i;
	int		index;
	t_lst	*ptr;

	if (!init_mutex(data))
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		index = i + 1;
		if (!creat_new_philo(data, index))
		{
			clean_up(data);
			return (0);
		}
		i++;
	}
	ptr = data->philos;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = data->philos;
	data->death_status = 1;
	return (1);
}
