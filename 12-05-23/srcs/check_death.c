/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:44:40 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/20 04:41:36 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_defines.h>
#include <philo_time.h>
#include <unistd.h>
#include <philo_struct.h>
#include <philosophers.h>
#include <stdio.h>

void	set_death(t_philo *self)
{
	pthread_mutex_lock(&self->stop_mutex);
	*self->stop = true;
	pthread_mutex_unlock(&self->stop_mutex);
	my_print(self, "Died");
}

bool	is_dead(t_philo *self)
{
	static bool somebody_is_dead;
	
	if (somebody_is_dead)
		return (false);
	if (get_timestamp_in_millisec(self->last_meal) > self->time_to_die)
		return (somebody_is_dead = true, true);
	return (false);
}

bool	have_to_quit(t_philo *self)
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
