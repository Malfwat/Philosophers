/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:44:40 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/17 18:29:16 by amouflet         ###   ########.fr       */
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
	usleep(10);
	pthread_mutex_lock(self->mutex_stop);
	*self->stop = true;
	pthread_mutex_unlock(self->mutex_stop);
	// printf("%-7.03lli %i Died\n", get_timestamp_in_millisec(self->start), self->index);
}

bool	is_dead(t_philo *self)
{
	if (get_timestamp_in_millisec(self->last_meal) > self->time_to_die)
		return (true);
	return (false);
}

bool	have_to_quit(t_philo *self)
{
	bool	exit_value;

	exit_value = false;
	usleep(10);
	pthread_mutex_lock(self->mutex_stop);
	if (*self->stop)
		exit_value = true;
	pthread_mutex_unlock(self->mutex_stop);
	return (exit_value);
}