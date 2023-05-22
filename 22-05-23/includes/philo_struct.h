/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:43:18 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/22 16:53:20 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>
# include <philo_defines.h>

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
	bool			stop;
	t_time			start;
	t_params		params;
	pthread_mutex_t	*cutlery;
	pthread_mutex_t	*mutex_stop;
	pthread_mutex_t	*mutex_print;
}t_table;

typedef struct	s_philosopher
{
	int				nb_meal_eaten;
	int				mutex_index[2];
	t_time			last_meal;
	t_table			*table;
	pthread_mutex_t	*mutex_print;
}t_philo;

typedef struct	s_supervisor
{
	t_table	*table;
	t_philo	*tab;
}t_supervisor;

#endif /* PHILO_STRUCT_H */
