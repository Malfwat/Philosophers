/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:13:43 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/24 17:33:14 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_defines.h>
#include <sys/time.h>
#include <stdlib.h>
#include <philo_defines.h>
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

t_time	get_departure_time(int table_len)
{
	return (get_time_point() + (LAUNCH_LAPS * (t_time)table_len));
}

bool	synchronize_launch(t_time time)
{
	while (time > get_time_point());
	return (true);
}
