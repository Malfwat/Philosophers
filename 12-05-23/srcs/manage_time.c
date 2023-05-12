/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:25:26 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/13 00:38:21 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <struct.h>

t_time	get_start(void)
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

/* #include <stdio.h>

int main(void)
{
    t_time	start = get_start();
    
    printf("%llu\n", get_timestamp_in_millisec(start));
    usleep(300000);
    printf("%llu\n", get_timestamp_in_millisec(start));
    usleep(300000);
    printf("%llu\n", get_timestamp_in_millisec(start));
} */