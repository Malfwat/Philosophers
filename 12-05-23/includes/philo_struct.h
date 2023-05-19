/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:58:02 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/20 00:35:47 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H 
# define STRUCT_H 

# include <pthread.h>
# include <stdbool.h>
# include <philo_defines.h>

typedef struct s_philosopher
{
	bool					*stop;
	int                     index;
	t_time					time_to_die;
	t_time					time_to_eat;
	t_time					time_to_sleep;
	int                     number_of_meal_needed;
	int                     number_of_meal_eaten;
	t_time					start;
	t_time					last_meal;
	t_time					actual_time;
	pthread_t               thread;
	pthread_mutex_t         mutex_stop;
	pthread_mutex_t         mutex_print;
	pthread_mutex_t         fork_mutex;
	pthread_mutex_t         *left_fork_mutex;
	struct s_philosopher    *prev;
	struct s_philosopher    *next;
}t_philo;

typedef struct s_pointer
{
	int					len;
	t_philo				*p_begin;
	t_philo				*p_current;
	t_philo				*p_end;
}t_table;

#endif /*STRUCT_H */