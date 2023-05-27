/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/28 01:04:20 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_time.h>
#include <philo_defines.h>
#include <philo_structs.h>
#include <stdio.h>
#include <philosophers.h>
#include <unistd.h>

void	*debug(void *addr)
{
	(void)addr;
	return (NULL);
}

void	routine_even(t_philo *philo)
{
	if (philo->index % 2)
	{
		my_print(philo, "is thinking");
		waiting(philo, philo->table->start, philo->table->params.eating);
	}	
}

// void	routine_odd(t_philo *philo)
// {
// 	if (philo->index % 3 == 0)
// 	{
// 		my_print(philo, "is thinking");
// 		waiting(philo, philo->table->start, philo->table->params.eating);
// 	}
// 	if (philo->index % 3 == 1)
// 	{
// 		my_print(philo, "is thinking");
// 		waiting(philo, philo->table->start, philo->table->params.eating * 2);
// 	}
// }

void	*routine(void	*ptr)
{
	t_philo		*philo;
	t_action	action[4];
	int			i;

	philo = (t_philo *)ptr;
	get_action_tab(action);
	synchronize_launch(philo->table->start);
	philo->last_meal = philo->table->start;
	// if (philo->table->params.nb_of_philo % 3 == 2)
		// routine_odd(philo);
	// else
	routine_even(philo);
	is_dead(philo);
	i = 0;
	while (!is_death(philo->table) && !are_fed_up(philo->table))
	{
		if (!action[i])
			i = 0;
		if (!action[i](philo))
			break ;
		is_dead(philo);
		i++;
	}
	return (NULL);
}

void	simulation(t_supervisor *supervisor)
{
	int	i;

	supervisor->table->start = get_departure_time(supervisor->table->params.nb_of_philo);
	i = -1;
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_create(&supervisor->philo_tab[i].thread, NULL, routine, &supervisor->philo_tab[i]);
	i = -1;
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_join(supervisor->philo_tab[i].thread, NULL);
}