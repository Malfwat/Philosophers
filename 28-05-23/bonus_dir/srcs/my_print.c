/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:14:00 by malfwa            #+#    #+#             */
/*   Updated: 2023/06/12 17:45:01 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus_struct.h>
#include <philo_bonus_time.h>
#include <philosopher_bonus.h>
#include <semaphore.h>
#include <stdio.h>

void	my_print(t_philo *philo, char *str)
{
	t_time	time;

	sem_wait(philo->sem_print);
	time = get_timestamp_in_millisec(philo->start);
	if (!is_death(philo))
		printf("%-7.03lli %i %s\n", time, philo->index, str);
	sem_post(philo->sem_print);
}
