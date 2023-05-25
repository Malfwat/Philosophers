/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/25 17:23:50 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_time.h>
#include <philo_defines.h>
#include <philo_structs.h>
#include <stdio.h>
#include <philosophers.h>
#include <unistd.h>

void	*routine(void	*ptr)
{
	t_time		time;
	t_philo		*philo;
	t_action	action[4];
	int			i;

	philo = (t_philo *)ptr;
	get_action_tab(action);
	synchronize_launch(philo->table->start);
	time = get_timestamp_in_millisec(philo->table->start);
	pthread_create(&philo->death_thread, NULL, death_routine, philo);
	// return (NULL);
	if (philo->index % 2 == 0)
	{
		think(philo);
		waiting(philo, philo->table->start, 10);
	}
	i = 0;
	while (!is_death(philo->table) && !are_fed_up(philo->table))
	{
		if (!action[i])
			i = 0;
		if (!action[i](philo))
			return (NULL);
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