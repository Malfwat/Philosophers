/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:25:26 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/20 04:27:16 by malfwa           ###   ########.fr       */
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

bool    synchronize_launch(t_philo *self)
{
    while (self->start / 1000 > get_time_point() / 1000)
		if (have_to_quit(self))
			return (false);
	return (true);
}

t_time	get_departure_time(int table_len)
{
	return (get_time_point() + (LAUNCH_LAPS * (t_time)table_len));
}
/* 
bool	wait_for_a_while(t_philo *self, t_case reason)
{
	t_time	time_point_sleep;
	bool	print;

	print = true;
	if (reason == EAT)
	{
		while (get_timestamp_in_millisec(self->last_meal) < self->time_to_eat)
		{
			if (is_dead(self))
				return (set_death(self), false);
			if (have_to_quit(self))
				return (false);
			if (print)
				my_print(self, "is eating");
			print = false;
		}
	}
	else if (reason == SLEEP)
	{
		time_point_sleep = get_time_point();
		// my_print(self, );
		while (get_timestamp_in_millisec(time_point_sleep) < self->time_to_sleep)
		{
			if (is_dead(self))
				return (set_death(self), false);
			if (have_to_quit(self))
				return (false);
			if (print)
				my_print(self, "Start sleeping");
			print = false;
		}
	}
	else if (reason == THINK)
	{
		my_print(self, "Start thinking");
		if (is_dead(self))
			return (set_death(self), false);
		if (have_to_quit(self))
			return (false);
	}
	return (true);
} */


bool	wait_for_a_while(t_philo *self, t_case reason)
{
	t_time	time_point;
	bool	print;

	print = true;
	if (reason == EAT || reason == SLEEP)
	{
		time_point = (t_time []){self->last_meal, get_time_point()}[reason];
		while (get_timestamp_in_millisec(time_point) < self->time_to_eat)
		{
			if (is_dead(self))
				return (set_death(self), false);
			if (have_to_quit(self))
				return (false);
			if (print)
				my_print(self, (char *[]){"is eating", "is sleeping"}[reason]);
			print = false;
		}
	}
	else if (reason == THINK)
	{
		my_print(self, "is thinking");
		if (is_dead(self))
			return (set_death(self), false);
		if (have_to_quit(self))
			return (false);
	}
	return (true);
}