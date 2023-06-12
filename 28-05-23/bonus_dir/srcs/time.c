/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:13:43 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/12 18:25:17 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus_defines.h>
#include <philo_bonus_struct.h>
#include <philosopher_bonus.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>

t_time	get_time_point(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

t_time	get_timestamp_in_millisec(t_time start)
{
	t_time	tmp;

	tmp = get_time_point();
	return ((tmp - start) / 1000);
}

t_time	get_departure_time(int table_len)
{
	return (get_time_point() + (LAUNCH_LAPS * (t_time)table_len));
}

void	synchronize_launch(t_time time)
{
	while (time > get_time_point())
		usleep(400);
}

bool	waiting(t_philo *philo, t_time time_point, t_time to_wait)
{
	while (get_timestamp_in_millisec(time_point) < to_wait)
	{
		is_dead(philo);
		if (is_death(philo))
			return (false);
		usleep(500);
	}
	return (true);
}
