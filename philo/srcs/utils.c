/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:19:27 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/14 08:07:04 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(t_philo *current, int message)
{
	time_t	time;

	pthread_mutex_lock(&current->data->death_mutex);
	pthread_mutex_lock(&current->data->print);
	time = get_time() - current->data->start_time;
	if (message == TAKE && current->data->death_status)
		printf("%.7li %i has taken a right fork\n", time, current->index);
	else if (message == EATING && current->data->death_status)
		printf("%.7li %i is eating\n", time, current->index);
	else if (message == SLEEPING && current->data->death_status)
		printf("%.7li %i is sleeping\n", time, current->index);
	else if (message == THINKING && current->data->death_status)
		printf("%.7li %i his thinking\n", time, current->index);
	else if (message == IS_DEAD)
		printf("%.7li %i dead\n", time, current->index);
	pthread_mutex_unlock(&current->data->print);
	pthread_mutex_unlock(&current->data->death_mutex);
}

time_t	get_time(void)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}

void	my_usleep(t_data *data, int deadline)
{
	time_t	start_time;
	int		work_time;

	if (deadline < 1000)
		usleep(deadline * 1000);
	else
	{
		work_time = 0;
		start_time = get_time();
		while (work_time < deadline)
		{
			pthread_mutex_lock(&data->death_mutex);
			if (!data->death_status)
			{
				pthread_mutex_unlock(&data->death_mutex);
				break ;
			}
			pthread_mutex_unlock(&data->death_mutex);
			work_time = (int)(get_time() - start_time);
			usleep(100);
		}
	}
}
