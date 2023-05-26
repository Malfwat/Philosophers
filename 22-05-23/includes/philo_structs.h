/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:43:18 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/26 19:53:22 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include <pthread.h>
# include <philo_defines.h>
# include <stdbool.h>

typedef struct s_params
{
	int	nb_of_philo;
	t_time	dying;
	t_time	eating;
	t_time	sleeping;
	int	nb_of_meal_needed;
}t_params;

typedef struct	s_table
{
	t_stop			stop;
	t_time			start;
	t_params		params;
	pthread_mutex_t	*mutex_cutlery;
	pthread_mutex_t	*mutex_stop;
	pthread_mutex_t	*mutex_print;
}t_table;

typedef struct	s_philosopher
{
	int				index;
	int				nb_meal_eaten;
	int				mutex_index[2];
	t_time			last_meal;
	t_table			*table;
	pthread_t		thread;
	pthread_t		death_thread;
	pthread_t		print_thread;
	pthread_mutex_t	mutex_eating;
	// pthread_mutex_t	*mutex_print;
}t_philo;

typedef struct	s_supervisor
{
	t_table	*table;
	t_philo	*philo_tab;
}t_supervisor;

typedef bool (*t_action)(t_philo *);


#endif /* PHILO_STRUCTS_H */
