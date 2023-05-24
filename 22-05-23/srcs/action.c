/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:49:41 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/24 13:33:48 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <pthread.h>
#include <philo_time.h>
#include <philo_structs.h>
#include <stdio.h>

void	drop_cutlery(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
	pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);
}

void	philo_sleep(t_philo *philo)
{
	t_time	time_point;

	drop_cutlery(philo);
	time_point = get_time_point();
	my_print(philo, "is sleeping");
	while (get_timestamp_in_millisec(time_point) < philo->table->params.sleeping)
	{
		if (philo->table->stop)
			return ;
	}
	return (think(philo));
}

bool	

void	eat(t_philo *philo)
{

	if (philo->table->stop)
		return ;
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);
		if (philo->table->stop)
		{
			pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);
			return ;
		}
		my_print(philo, "Has taken a fork");
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
		if (philo->table->stop)
			return (drop_cutlery(philo));
		my_print(philo, "is eating");
	}
	else
	{
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
		if (philo->table->stop)
		{
			pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
			return ;
		}
		my_print(philo, "Has taken a fork");
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);
		if (philo->table->stop)
			return (drop_cutlery(philo));
		my_print(philo, "is eating");
	}
	pthread_mutex_lock(&philo->mutex_eating);
	philo->last_meal = get_time_point();
	pthread_mutex_unlock(&philo->mutex_eating);
	while (get_timestamp_in_millisec(philo->last_meal) < philo->table->params.eating)
		if (philo->table->stop)
			return (drop_cutlery(philo));
	pthread_mutex_lock(&philo->mutex_eating);
	philo->nb_meal_eaten += 1;
	pthread_mutex_unlock(&philo->mutex_eating);
	if (philo->nb_meal_eaten == philo->table->params.nb_of_meal_needed)
	{
		pthread_mutex_lock(philo->table->mutex_stop);
		philo->table->stop++;
		pthread_mutex_unlock(philo->table->mutex_stop);
	}
	if (philo->table->stop)
		return (drop_cutlery(philo));
	return (philo_sleep(philo));
}

void	think(t_philo *philo)
{
	if (philo->table->stop)
		return ;
	my_print(philo, "is thinking");
	return (eat(philo));
}
