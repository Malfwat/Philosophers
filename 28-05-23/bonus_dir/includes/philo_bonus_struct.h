/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:19:31 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/09 21:11:17 by malfwa           ###   ########.fr       */
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
	sem_t			*sem_death; // just one sem initialized at 0 and if someone died he has to do nb post so everyone can stop
	sem_t			**sem_fed; // nb of philo initialized a nb philo so each philo will pass by each case so they know when the simulation is over
	char			**fed_sem_names;
	// pthread_mutex_t	death_mut; // so the thread can modify the semaphore
	// pthread_mutex_t	fed_mut; // so the thread can modify the semaphore by waiting
	pthread_mutex_t	stop_mutx;
}t_over;

typedef struct s_philo
{
	int			index; // from 1 to nb philo
	int			nb_meal_eaten;
	sem_t		*cutlery; // nb philo cutlery represented in tab with sem at 1
	sem_t		*sem_print;
	t_over		supervise;
	t_time		start;
	t_time		last_meal;
	t_params	params;
	// pthread_mutex_t	eat_mutx;
}t_philo;

typedef bool	(*t_action)(t_philo *);

#endif /* PHILO_BONUS_STRUCT_H */