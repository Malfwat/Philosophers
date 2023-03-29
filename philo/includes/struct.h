/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:58:02 by malfwa            #+#    #+#             */
/*   Updated: 2023/03/27 18:20:14 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H 
# define STRUCT_H 

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philosopher
{
	bool					*stop;
	int                     index;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	int                     number_of_meal_needed;
	int                     number_of_meal_eaten;
	unsigned long long		start;
	unsigned long long		last_meal;
	unsigned long long		actual_time;
	pthread_t               thread;
	pthread_mutex_t         *mutex;
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