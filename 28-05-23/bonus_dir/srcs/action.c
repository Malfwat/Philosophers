/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:54:32 by malfwa            #+#    #+#             */
/*   Updated: 2023/06/12 18:25:48 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher_bonus.h>
#include <philo_bonus_defines.h>
#include <philo_bonus_struct.h>
#include <philo_bonus_time.h>

bool	eat(t_philo *philo)
{
	bool		exit_value;

	if (!get_cutlery(philo))
		return (false);
	my_print(philo, "is eating");
	add_meal(philo);
	exit_value = waiting(philo, philo->last_meal, philo->params.eating);
	drop_cutlery(philo->cutlery);
	return (exit_value);
}

bool	philo_sleep(t_philo *philo)
{
	bool	exit_value;

	my_print(philo, "is sleeping");
	exit_value = waiting(philo, philo->last_meal + \
	philo->params.sleeping * 1000, \
	philo->params.sleeping);
	return (exit_value);
}

bool	think(t_philo *philo)
{
	t_time	t_eat;
	int		nb_p;

	if (is_death(philo))
		return (false);
	my_print(philo, "is thinking");
	t_eat = philo->params.eating;
	nb_p = philo->params.nb_philo;
	if (nb_p % 2)
		return (waiting(philo, philo->last_meal, \
			t_eat * 2 + t_eat / 2));
	return (waiting(philo, philo->last_meal, t_eat + t_eat / 2));
}

void	get_action_tab(t_action *tab)
{
	tab[0] = &eat;
	tab[1] = &philo_sleep;
	tab[2] = &think;
	tab[3] = NULL;
}

void	add_meal(t_philo *philo)
{
	philo->nb_meal_eaten += 1;
	if (philo->nb_meal_eaten == philo->params.nb_meal_needed)
	{
		incremt_sem(philo->supervise.sem_fed \
		[philo->index - 1], philo->params.nb_philo);
	}
}
