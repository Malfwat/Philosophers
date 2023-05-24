/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:49:41 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/24 17:35:30 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <pthread.h>
#include <philo_time.h>
#include <philo_structs.h>
#include <stdio.h>

bool	waiting(t_philo *philo, t_time time_point, t_time to_wait)
{
	while (get_timestamp_in_millisec(time_point) > to_wait)
	{
		if (is_dead(philo))
			return (false);
	}
	return (true);
}
	
void	eat(t_philo *philo)
{
	
}

void	philo_sleep(t_philo *philo)
{
	
}

void	think(t_philo *philo)
{
	
}

void	get_action_tab(t_action **tab)
{
	(*tab)[0] = &eat;
	(*tab)[1] = &philo_sleep;
	(*tab)[2] = &think;
	(*tab)[3] = NULL;
}
