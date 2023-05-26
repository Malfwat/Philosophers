/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:49:41 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/26 12:29:12 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <pthread.h>
#include <philo_time.h>
#include <philo_structs.h>
#include <philo_defines.h>
#include <stdio.h>
#include <unistd.h>

bool	waiting(t_philo *philo, t_time time_point, t_time to_wait)
{
	while (get_timestamp_in_millisec(time_point) < to_wait)
	{
		if (is_death(philo->table))
			return (false);
	}
	return (true);
}

void	drop_cutlery(t_philo *philo, enum e_fork *tab)
{
	pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[FIRST]]);
	pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[SEC]]);
}

bool	get_cutlery(t_philo *philo, enum e_fork *tab)
{
	pthread_mutex_lock(&philo->table->mutex_cutlery[tab[FIRST]]);
	if (is_death(philo->table))
	{
		pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[FIRST]]);
		return (false);
	}
	my_print(philo, "has taken a fork");
	if (philo->table->params.nb_of_philo == 1)
	{
		pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[FIRST]]);
		waiting(philo, philo->table->start, philo->table->params.dying + 1);
		return (is_dead(philo), set_death(philo->table));
	}
	pthread_mutex_lock(&philo->table->mutex_cutlery[tab[SEC]]);
	if (is_death(philo->table))
		return (drop_cutlery(philo, tab), false);
	pthread_mutex_lock(&philo->mutex_eating);
	philo->last_meal = get_time_point();
	pthread_mutex_lock(&philo->mutex_eating);
	return (true);
}

bool	eat(t_philo *philo)
{
	bool		exit_value;
	enum e_fork	tab[2];

	if (philo->index % 2 == 1)
	{
		tab[FIRST] = philo->mutex_index[RIGHT_FORK];
		tab[SEC] = philo->mutex_index[MY_FORK];
	}
	else
	{
		tab[FIRST] = philo->mutex_index[MY_FORK];
		tab[SEC] = philo->mutex_index[RIGHT_FORK];
	}
	if (!get_cutlery(philo, tab))
		return (false);
	my_print(philo, "is eating");
	add_meal(philo);
	exit_value = waiting(philo, philo->last_meal, philo->table->params.eating);
	drop_cutlery(philo, tab);
	return (exit_value);
}

bool	philo_sleep(t_philo *philo)
{
	bool	exit_value;
	
	my_print(philo, "is sleeping");
	exit_value = waiting(philo, get_time_point(), philo->table->params.sleeping);
	return (exit_value);
}

bool	think(t_philo *philo)
{
	t_time	t_eat;

	my_print(philo, "is thinking");
	if (is_death(philo->table))
		return (false);
	t_eat = philo->table->params.eating;
	return (waiting(philo, philo->last_meal, t_eat * 2 - 1));
}

void	get_action_tab(t_action *tab)
{
	tab[0] = &eat;
	tab[1] = &philo_sleep;
	tab[2] = &think;
	tab[3] = NULL;
}
