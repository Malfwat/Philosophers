/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:51:30 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/26 19:53:38 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_defines.h>
#include <philo_structs.h>
#include <philo_time.h>
#include <philosophers.h>
#include <pthread.h>
#include <stdio.h>

void	my_print(t_philo *philo, char *str)
{
	t_time	time;

	pthread_mutex_lock(philo->table->mutex_print);
	time = get_timestamp_in_millisec(philo->table->start);
	if (!is_death(philo->table))
		printf("%-7.03lli %i %s\n", time, philo->index, str);
	pthread_mutex_unlock(philo->table->mutex_print);
}