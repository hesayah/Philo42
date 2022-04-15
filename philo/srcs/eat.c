/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:06:50 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/16 01:40:58 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	nb_eat_gestion(t_philo *current, int option)
{
	pthread_mutex_lock(&current->eat_status_mutex);
	if (option == 0)
	{
		if (current->eat_status == 0)
		{
			pthread_mutex_unlock(&current->eat_status_mutex);
			return (0);
		}
		pthread_mutex_unlock(&current->eat_status_mutex);
		return (1);
	}
	else if (option == 1)
		current->eat_status--;
	pthread_mutex_unlock(&current->eat_status_mutex);
	return (1);
}

void	fork_gestion_last(t_philo *current, t_philo *next)
{
	pthread_mutex_lock(&next->fork_mutex);
	if (next->fork == 0)
	{
		next->fork = 1;
		print_message(current, TAKE);
		pthread_mutex_lock(&current->fork_mutex);
		if (current->fork == 0)
		{
			current->fork = 1;
			print_message(current, TAKE);
			pthread_mutex_lock(&current->last_eat_mutex);
			current->last_eat = get_time();
			pthread_mutex_unlock(&current->last_eat_mutex);
			nb_eat_gestion(current, 1);
			print_message(current, EATING);
			my_usleep(current->data, current->data->time_eat);
			current->fork = 0;
			next->fork = 0;
		}
		pthread_mutex_unlock(&current->fork_mutex);
	}
	pthread_mutex_unlock(&next->fork_mutex);
}

void	fork_gestion(t_philo *current, t_philo *next)
{
	pthread_mutex_lock(&current->fork_mutex);
	if (current->fork == 0)
	{
		current->fork = 1;
		print_message(current, TAKE);
		pthread_mutex_lock(&next->fork_mutex);
		if (next->fork == 0)
		{
			next->fork = 1;
			print_message(current, TAKE);
			pthread_mutex_lock(&current->last_eat_mutex);
			current->last_eat = get_time();
			pthread_mutex_unlock(&current->last_eat_mutex);
			nb_eat_gestion(current, 1);
			print_message(current, EATING);
			my_usleep(current->data, current->data->time_eat);
			current->fork = 0;
			next->fork = 0;
		}
		pthread_mutex_unlock(&next->fork_mutex);
	}
	pthread_mutex_unlock(&current->fork_mutex);
}

void	eat_gestion(t_lst *philo_lst)
{
	t_lst		*philo_next;
	t_philo		*current;
	t_philo		*next;

	philo_next = philo_lst->next;
	current = (t_philo *)philo_lst->content;
	next = (t_philo *)philo_next->content;
	if (current->index != current->data->nb_philo)
		fork_gestion(current, next);
	else
		fork_gestion_last(current, next);
}
