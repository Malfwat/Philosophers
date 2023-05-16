/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:25:26 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/16 21:43:32 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <philo_struct.h>
#include <philo_defines.h>
#include <philosophers.h>

t_time	get_time_point(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

t_time	get_timestamp_in_millisec(t_time start)
{
	struct timeval		tv;
	unsigned long long	tmp;

	gettimeofday(&tv, NULL);
	tmp = tv.tv_sec * 1000000 + tv.tv_usec;
	return ((tmp - start) / 1000);
}

void    synchronize_launch(t_time departure)
{
    while (departure / 1000 != get_time_point() / 1000)
        usleep(1000);
}

t_time	get_departure_time(int table_len)
{
	return (get_time_point() + LAUNCH_LAPS * (unsigned long long)table_len);
}

bool	wait_for_a_while(t_philo *self, t_case reason)
{
	t_time	period[2];
	
	period[0] = self->time_to_eat;
	period[1] = self->time_to_sleep;
	if (reason == EAT || reason == SLEEP)
	{
		while (get_timestamp_in_millisec(self->last_meal) < period[reason])
		{
			if (is_dead(self))
				return (set_death(self), false);
			if (have_to_quit(self))
				return (false);
			usleep(1000);
		}
	}
	else if (reason == THINK)
	{
		if (is_dead(self))
			return (set_death(self), false);
		if (have_to_quit(self))
			return (false);
		printf("%-7.03lli %i Start thinking\n", get_timestamp_in_millisec(self->start), self->index);
	}
	return (true);
}
