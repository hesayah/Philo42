/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:57:22 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/14 04:28:22 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean_lst(t_lst **lst, int nb_philo)
{
	int					index;
	t_lst				*current;
	t_lst				*tmp;
	t_philo				*philo;

	current = *lst;
	index = 0;
	while (++index <= nb_philo)
	{
		tmp = current;
		current = tmp->next;
		philo = (t_philo *)tmp->content;
		pthread_mutex_destroy(&(philo)->fork_mutex);
		pthread_mutex_destroy(&(philo)->last_eat_mutex);
		pthread_mutex_destroy(&(philo)->eat_status_mutex);
		free(philo);
		free(tmp);
	}
}

void	clean_up(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
		clean_lst(&data->philos, data->nb_philo);
}
