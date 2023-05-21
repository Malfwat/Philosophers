/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:25:26 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/21 22:48:20 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <philo_struct.h>
#include <philo_defines.h>
#include <philosophers.h>
#include <stdbool.h>

t_time	get_time_point(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

t_time	get_timestamp_in_millisec(t_time start)
{
	t_time	tmp;

	tmp = get_time_point();
	return ((tmp - start) / 1000);
}

bool    synchronize_launch(t_pairs *self)
{
	t_time	start;

	start = self->start;
    while (start / 1000 > get_time_point() / 1000)
		continue ;
		// if (have_to_quit(self))
			// return (false);
	return (true);
}

t_time	get_departure_time(int table_len)
{
	return (get_time_point() + (LAUNCH_LAPS * (t_time)table_len));
}

bool	wait_for_a_while(t_pairs *self, t_case reason)
{
	t_time	time_point;
	t_time	duration;

	if (reason == EAT || reason == SLEEP)
	{
		pthread_mutex_lock(&self->mutex_philo);
		duration = (t_time []){self->philo->time_to_eat, self->philo->time_to_sleep}[reason];
		time_point = (t_time []){self->philo->last_meal, get_time_point()}[reason];
		my_print(self, (char *[]){"is eating", "is sleeping"}[reason], reason);
		pthread_mutex_unlock(&self->mutex_philo);
		while (get_timestamp_in_millisec(time_point) < duration)
		{
			if (have_to_quit(self))
				return (false);
		}
	}
	else if (reason == THINK)
	{
		my_print(self, "is thinking", reason);
		if (have_to_quit(self))
			return (false);
	}
	return (true);
}
