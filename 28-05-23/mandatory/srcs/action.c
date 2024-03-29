/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:49:41 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/28 22:58:17 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philo_time.h>
#include <philo_structs.h>
#include <philo_defines.h>
#include <philo_actions.h>

bool	eat(t_philo *philo)
{
	bool		exit_value;
	enum e_fork	tab[2];

	if (philo->index % 2 == 0)
	{
		tab[FIRST] = philo->mutex_index[RIGHT_FORK];
		tab[SEC] = philo->mutex_index[LEFT_FORK];
	}
	else
	{
		tab[FIRST] = philo->mutex_index[LEFT_FORK];
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
	exit_value = waiting(philo, get_time_point(), \
	philo->table->params.sleeping);
	return (exit_value);
}

bool	think(t_philo *philo)
{
	t_time	t_eat;
	int		nb_p;

	if (is_death(philo->table))
		return (false);
	my_print(philo, "is thinking");
	t_eat = philo->table->params.eating;
	nb_p = philo->table->params.nb_of_philo;
	if (nb_p % 2)
		return (waiting(philo, philo->last_meal, t_eat * 2 + t_eat / 2));
	return (waiting(philo, philo->last_meal, t_eat + t_eat / 2));
}

void	get_action_tab(t_action *tab)
{
	tab[0] = &eat;
	tab[1] = &philo_sleep;
	tab[2] = &think;
	tab[3] = NULL;
}
