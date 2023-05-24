/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:18:17 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/24 18:17:24 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_defines.h>
#include <philo_structs.h>
#include <philo_time.h>
#include <pthread.h>

bool	set_death(t_table *table)
{
	pthread_mutex_lock(table->mutex_stop);
	table->stop = DEATH;
	pthread_mutex_unlock(table->mutex_stop);
	return (false);
}

bool	is_death(t_table *table)
{
	if (table->stop == DEATH)
		return (true);
	return (false);
}

bool	is_dead(t_philo *philo)
{
	t_time	time_to_die;

	time_to_die = philo->table->params.dying;
	if (!philo->last_meal)
	{
		if (get_timestamp_in_millisec(philo->table->start) > time_to_die)
			return (true);
	}
	else
	{
		if (get_timestamp_in_millisec(philo->last_meal) > time_to_die)
			return (true);
	}
	return (false);
}

bool	are_fed_up(t_table *table)
{
	if (table->stop == table->params.nb_of_philo)
		return (true);
	return (false);
}

void	add_meal(t_philo *philo)
{
	philo->nb_meal_eaten += 1;
	if (philo->nb_meal_eaten == philo->table->params.nb_of_meal_needed)
	{
		pthread_mutex_lock(philo->table->mutex_stop);
		philo->table->stop += 1;
		pthread_mutex_unlock(philo->table->mutex_stop);
	}
}
