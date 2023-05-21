/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:44:40 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/21 22:42:13 by malfwa           ###   ########.fr       */
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
	my_print(self, "Died", DIE);
	pthread_mutex_unlock(&self->mutex_philo);
}

bool	is_dead(t_pairs *self)
{
	static bool somebody_is_dead;
	t_philo	*philo;
	
	if (somebody_is_dead)
		return (false);
	pthread_mutex_lock(&self->mutex_philo);
	philo = self->philo;
	if (philo->done_eating)
		return (pthread_mutex_unlock(&self->mutex_philo), false);
	if (get_timestamp_in_millisec(philo->last_meal) > philo->time_to_die)
	{
		pthread_mutex_unlock(&self->mutex_philo);
		return (somebody_is_dead = true, true);
	}
	pthread_mutex_unlock(&self->mutex_philo);
	return (false);
}

bool	have_to_quit(t_pairs *self)
{
	bool	return_value;
	t_philo	*philo;

	return_value = false;
	pthread_mutex_lock(&self->mutex_philo);
	philo = self->philo;
	pthread_mutex_lock(&philo->stop_mutex);
	if (*philo->stop)
		return_value = true;
	pthread_mutex_unlock(&philo->stop_mutex);
	pthread_mutex_unlock(&self->mutex_philo);
	return (return_value);
}
