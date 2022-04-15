/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:32:03 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/14 05:57:50 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*dinner(void *param)
{
	t_lst	*philo;
	t_lst	*ptr;
	t_philo	*current;

	philo = (t_lst *)param;
	current = philo->content;
	if (!(current->index % 2))
		my_usleep(current->data, current->data->time_eat);
	while (dead_gestion(current->data) && nb_eat_gestion(current, 0))
	{
		if (current->data->nb_philo > 1)
		{
			eat_gestion(philo);
			print_message(current, SLEEPING);
			my_usleep(current->data, current->data->time_sleep);
			print_message(current, THINKING);
		}
	}
}

int	join_all(t_data *data)
{
	int		index;
	t_lst	*philo_lst;
	t_philo	*info;

	index = 0;
	philo_lst = data->philos;
	while (index < data->nb_philo)
	{
		info = philo_lst->content;
		pthread_join(info->thrd_philo, NULL);
		philo_lst = philo_lst->next;
		index++;
	}
	pthread_join(data->die, NULL);
	clean_up(data);
	return (0);
}

int	run(t_data *data)
{	
	int		index;
	t_lst	*philo_lst;
	t_philo	*info;

	data->start_time = get_time();
	index = 0;
	philo_lst = data->philos;
	while (index < data->nb_philo)
	{
		info = philo_lst->content;
		info->last_eat = get_time();
		pthread_create(&(info->thrd_philo), NULL, dinner, (void *)philo_lst);
		philo_lst = philo_lst->next;
		index++;
	}
	pthread_create(&(data->die), NULL, dead, (void *)data);
	return (join_all(data));
}
