/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesayah <hesayah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 02:30:47 by hesayah           #+#    #+#             */
/*   Updated: 2022/04/14 06:35:44 by hesayah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define TAKE 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define IS_DEAD 5

typedef struct s_lst
{
	void			*content;
	void			*next;
}					t_lst;

typedef struct s_data
{
	time_t			start_time;
	pthread_t		die;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				round;
	t_lst			*philos;
	pthread_mutex_t	death_mutex;
	int				death_status;
	pthread_mutex_t	print;
}					t_data;

typedef struct s_philo
{
	pthread_t		thrd_philo;
	int				index;
	pthread_mutex_t	fork_mutex;
	int				fork;
	pthread_mutex_t	last_eat_mutex;
	time_t			last_eat;
	pthread_mutex_t	eat_status_mutex;
	int				eat_status;
	t_data			*data;
}					t_philo;

int					init_dinner(t_data *data);
int					run(t_data *data);
void				eat_gestion(t_lst *philo_lst);
void				print_message(t_philo *current, int message);
time_t				get_time(void);
void				*dead(void *params);
int					dead_gestion(t_data *data);
int					check_deadh(t_philo *current);
int					nb_eat_gestion(t_philo *current, int option);
void				my_usleep(t_data *data, int deadline);
void				clean_up(t_data *data);

#endif