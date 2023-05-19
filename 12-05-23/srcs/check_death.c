/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:44:40 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/20 00:36:50 by malfwa           ###   ########.fr       */
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
	// usleep(10);
	pthread_mutex_lock(&self->mutex_stop);
	*self->stop = true;
	pthread_mutex_unlock(&self->mutex_stop);
	print_mutex(self, "Died");
	// printf("Died\n");
}

bool	is_dead(t_philo *self)
{
	if (get_timestamp_in_millisec(self->last_meal) > self->time_to_die)
		return (true);
	return (false);
}

bool	have_to_quit(t_philo *self)
{
	bool	return_value;

	return_value = false;
	usleep(10);
	pthread_mutex_lock(&self->mutex_stop);
	if (*self->stop)
		return_value = true;
	pthread_mutex_unlock(&self->mutex_stop);
	return (return_value);
}
