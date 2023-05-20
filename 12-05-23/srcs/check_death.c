/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:44:40 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/20 15:53:10 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_defines.h>
#include <philo_time.h>
#include <unistd.h>
#include <philo_struct.h>
#include <philosophers.h>
#include <stdio.h>

void	set_death(t_pairs *self)
{
	t_philo	*philo;
	
	pthread_mutex_lock(&self->mutex_philo);
	philo = self->philo;
	pthread_mutex_lock(&philo->stop_mutex);
	*philo->stop = true;
	pthread_mutex_unlock(&philo->stop_mutex);
	my_print(philo, "Died");
	pthread_mutex_unlock(&self->mutex_philo);
}

bool	is_dead(t_pairs *self)
{
	static bool somebody_is_dead;
	
	if (somebody_is_dead)
		return (false);
	if (get_timestamp_in_millisec(self->last_meal) > self->time_to_die)
		return (somebody_is_dead = true, true);
	return (false);
}

bool	have_to_quit(t_pairs *self)
{
	bool	return_value;

	return_value = false;
	// usleep(10);
	pthread_mutex_lock(&self->stop_mutex);
	if (*self->stop)
		return_value = true;
	pthread_mutex_unlock(&self->stop_mutex);
	return (return_value);
}
