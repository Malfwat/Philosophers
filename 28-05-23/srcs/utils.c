/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:18:17 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/28 11:49:16 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_defines.h>
#include <philo_structs.h>
#include <philo_time.h>
#include <pthread.h>

bool	set_death(t_table *table)
{
	pthread_mutex_lock(&table->mutex_stop);
	table->stop = DEATH;
	pthread_mutex_unlock(&table->mutex_stop);
	return (false);
}

bool	is_death(t_table *table)
{
	bool	exit_value;

	exit_value = false;
	pthread_mutex_lock(&table->mutex_stop);
	if (table->stop == DEATH)
		exit_value = true;
	pthread_mutex_unlock(&table->mutex_stop);
	return (exit_value);
}

bool	is_dead(t_philo *philo)
{
	t_time	time_to_die;
	t_time	time_point;

	time_to_die = philo->table->params.dying;
	time_point = philo->last_meal;
	if (get_timestamp_in_millisec(time_point) > time_to_die)
	{
		my_print(philo, "is dead");
		return (set_death(philo->table));
	}
	return (true);
}

bool	are_fed_up(t_table *table)
{
	bool	exit_value;

	exit_value = false;
	pthread_mutex_lock(&table->mutex_stop);
	if (table->stop == table->params.nb_of_philo)
		exit_value = true;
	pthread_mutex_unlock(&table->mutex_stop);
	return (exit_value);
}

void	add_meal(t_philo *philo)
{
	philo->nb_meal_eaten += 1;
	if (philo->nb_meal_eaten == philo->table->params.nb_of_meal_needed)
	{
		pthread_mutex_lock(&philo->table->mutex_stop);
		philo->table->stop += 1;
		pthread_mutex_unlock(&philo->table->mutex_stop);
	}
}
