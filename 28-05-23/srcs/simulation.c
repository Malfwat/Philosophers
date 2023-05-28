/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/28 03:01:58 by malfwa           ###   ########.fr       */
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

void	spread_launch(t_philo *philo)
{
	int	nb_p;

	nb_p = philo->table->params.nb_of_philo;
	my_print(philo, "is thinking");
	if (nb_p % 2 && philo->index == nb_p)
		waiting(philo, philo->table->start, philo->table->params.eating + philo->table->params.eating / 2);
	else if (philo->index % 2)
		waiting(philo, philo->table->start, philo->table->params.eating);
}

void	*routine(void	*ptr)
{
	t_philo		*philo;
	t_action	action[4];
	int			i;

	philo = (t_philo *)ptr;
	get_action_tab(action);
	synchronize_launch(philo->table->start);
	philo->last_meal = philo->table->start;
	spread_launch(philo);
	is_dead(philo);
	i = 0;
	while (!is_death(philo->table) && !are_fed_up(philo->table))
	{
		if (!action[i])
			i = 0;
		is_dead(philo);
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