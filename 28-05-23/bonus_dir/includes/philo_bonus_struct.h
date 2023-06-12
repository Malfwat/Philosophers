/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:19:31 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/12 18:27:18 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_STRUCT_H
# define PHILO_BONUS_STRUCT_H

# include <semaphore.h>
# include <pthread.h>
# include <stdbool.h>
# include <philo_bonus_defines.h>

typedef struct s_params
{
	int		nb_philo;
	t_time	dying;
	t_time	eating;
	t_time	sleeping;
	int		nb_meal_needed;
}t_params;

typedef struct s_end_of_simulation
{
	bool			stop;
	pthread_t		check_death;
	pthread_t		check_fed;
	sem_t			*sem_death;
	sem_t			**sem_fed;
	char			**fed_sem_names;
	pthread_mutex_t	stop_mutx;
}t_over;

typedef struct s_philo
{
	int			index;
	int			nb_meal_eaten;
	sem_t		*cutlery;
	sem_t		*sem_print;
	sem_t		*sem_to_take;
	t_over		supervise;
	t_time		start;
	t_time		last_meal;
	t_params	params;
}t_philo;

typedef bool	(*t_action)(t_philo *);

#endif /* PHILO_BONUS_STRUCT_H */