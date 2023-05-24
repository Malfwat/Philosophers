/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:49:41 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/24 18:25:14 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <pthread.h>
#include <philo_time.h>
#include <philo_structs.h>
#include <philo_defines.h>
#include <stdio.h>

bool	waiting(t_philo *philo, t_time time_point, t_time to_wait)
{
	while (get_timestamp_in_millisec(time_point) < to_wait)
	{
		if (is_dead(philo))
			return (set_death(philo->table));
		if (is_death(philo->table))
			return (false);
	}
	return (true);
}
	
bool	eat(t_philo *philo)
{
	enum e_fork	tab[2];
	bool		exit_value;
	
	if (philo->index % 2)
	{
		tab[FIRST] = philo->mutex_index[RIGHT_FORK];
		tab[SEC] = philo->mutex_index[MY_FORK];
	}
	else
	{
		tab[FIRST] = philo->mutex_index[MY_FORK];
		tab[SEC] = philo->mutex_index[RIGHT_FORK];
	}
	pthread_mutex_lock(&philo->table->mutex_cutlery[tab[FIRST]]);
	if (is_dead(philo) && !set_death(philo->table))
		my_print(philo, "is dead");
	if (is_death(philo->table))
	{
		pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[FIRST]]);
		return (false);
	}
	my_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->mutex_cutlery[tab[SEC]]);
	if (is_dead(philo) && !set_death(philo->table))
		my_print(philo, "is dead");
	if (is_death(philo->table))
	{
		pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[FIRST]]);
		pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[SEC]]);
		return (false);
	}
	my_print(philo, "is eating");
	exit_value = waiting(philo, philo->last_meal, philo->table->params.eating);
	pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[FIRST]]);
	pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[SEC]]);
	add_meal(philo);
	return (exit_value);
}

bool	philo_sleep(t_philo *philo)
{
	my_print(philo, "is sleeping");
	return (waiting(philo, philo->last_meal, philo->table->params.sleeping));
}

bool	think(t_philo *philo)
{
	t_time	time_point;

	time_point = get_time_point();
	my_print(philo, "is thinking");
	return (waiting(philo, time_point, 1000));
}

void	get_action_tab(t_action *tab)
{
	tab[0] = &eat;
	tab[1] = &philo_sleep;
	tab[2] = &think;
	tab[3] = NULL;
}
