/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutlery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:41:21 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/28 22:55:12 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philo_structs.h>
#include <philo_time.h>
#include <philo_actions.h>

void	drop_cutlery(t_philo *philo, enum e_fork *tab)
{
	pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[FIRST]]);
	pthread_mutex_unlock(&philo->table->mutex_cutlery[tab[SEC]]);
}

bool	get_cutlery(t_philo *philo, enum e_fork *tab)
{
	pthread_mutex_lock(&philo->table->mutex_cutlery[tab[FIRST]]);
	is_dead(philo);
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
		return (is_dead(philo));
	}
	pthread_mutex_lock(&philo->table->mutex_cutlery[tab[SEC]]);
	is_dead(philo);
	if (is_death(philo->table))
		return (drop_cutlery(philo, tab), false);
	philo->last_meal = get_time_point();
	return (true);
}
