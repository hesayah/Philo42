/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:30:59 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/14 07:36:48 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead_gestion(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 0)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->death_mutex);
	usleep(50);
	return (1);
}

int	check_deadh(t_philo *current)
{
	time_t	time;

	pthread_mutex_lock(&current->last_eat_mutex);
	time = get_time() - current->data->start_time;
	if (get_time() - current->last_eat >= current->data->time_die
		&& nb_eat_gestion(current, 0))
	{
		pthread_mutex_lock(&current->data->death_mutex);
		current->data->death_status = 0;
		pthread_mutex_unlock(&current->data->death_mutex);
		print_message(current, IS_DEAD);
		pthread_mutex_unlock(&current->last_eat_mutex);
		return (0);
	}
	if (!nb_eat_gestion(current, 0))
	{
		pthread_mutex_unlock(&current->last_eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&current->last_eat_mutex);
	return (1);
}

void	*dead(void *params)
{
	t_lst	*ptr;
	t_lst	*philo_lst;
	t_data	*data;

	data = (t_data *)params;
	philo_lst = data->philos;
	ptr = philo_lst;
	while (data->nb_philo)
	{
		if (!check_deadh(ptr->content))
			break ;
		ptr = ptr->next;
	}
}
