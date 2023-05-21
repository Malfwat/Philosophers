/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:58:02 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/21 17:48:24 by malfwa           ###   ########.fr       */
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
	bool					done_eating;
	int                     index;
	int                     number_of_meal_needed;
	int                     number_of_meal_eaten;
	t_time					time_to_eat;
	t_time					time_to_die;
	t_time					time_to_sleep;
	t_time					last_meal;
	pthread_t               thread;
	pthread_mutex_t         self_mutex;
	pthread_mutex_t         stop_mutex;
	pthread_mutex_t         fork_mutex;
	pthread_mutex_t         *left_fork_mutex;
	struct s_philosopher    *prev;
	struct s_philosopher    *next;
}t_philo;

typedef struct s_philo_mutex_couple
{
	t_philo						*philo;
	t_time						start;
	pthread_mutex_t				print_mutex;
	pthread_mutex_t				mutex_philo;
	struct s_philo_mutex_couple	*next;
	struct s_philo_mutex_couple	*prev;
}t_pairs;

typedef struct s_pairs_cursor
{
	t_pairs	*begin;
	t_pairs	*current;
	t_pairs	*end;
}	t_pairs_cursor;


typedef struct s_pointer
{
	int					len;
	
	t_pairs			*lst_of_pairs;
	t_pairs			*lst_of_pairs_begin;
	t_pairs			*arg;
	t_philo			*p_begin;
	t_philo			*p_current;
	t_philo			*p_end;
	t_time  		departure;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}t_table;

#endif /*STRUCT_H */