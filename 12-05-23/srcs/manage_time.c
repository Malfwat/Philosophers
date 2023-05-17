/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:25:26 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/17 18:45:22 by amouflet         ###   ########.fr       */
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

void    synchronize_launch(t_time departure)
{
    while (departure / 1000 > get_time_point() / 1000);
}

t_time	get_departure_time(int table_len)
{
	return (get_time_point() + (LAUNCH_LAPS * (unsigned long long)table_len));
}

bool	wait_for_a_while(t_philo *self, t_case reason)
{
	t_time	time_point_sleep;
	t_time	timestamp_from_start;
	bool	print;

	if (reason == EAT)
	{
		timestamp_from_start = get_timestamp_in_millisec(self->start);
		print = true;
		while (get_timestamp_in_millisec(self->last_meal) < self->time_to_eat)
		{
			if (is_dead(self))
				return (set_death(self), false);
			if (have_to_quit(self))
				return (false);
			if (print)
				printf("%-7.03lli %i Has taken a fork\n", get_timestamp_in_millisec(self->start), self->index);
			print = false;
		}
	}
	else if (reason == SLEEP)
	{
		time_point_sleep = get_time_point();
		timestamp_from_start = get_timestamp_in_millisec(self->start);
		printf("%-7.03lli %i Start sleeping\n", timestamp_from_start, self->index);
		while (get_timestamp_in_millisec(time_point_sleep) < self->time_to_sleep)
		{
			if (is_dead(self))
				return (set_death(self), false);
			if (have_to_quit(self))
				return (false);
		}
	}
	else if (reason == THINK)
	{
		timestamp_from_start = get_timestamp_in_millisec(self->start);
		printf("%-7.03lli %i Start thinking\n", timestamp_from_start, self->index);
		if (is_dead(self))
			return (set_death(self), false);
		if (have_to_quit(self))
			return (false);
	}
	return (true);
}
