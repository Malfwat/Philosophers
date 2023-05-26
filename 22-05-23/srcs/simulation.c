/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/26 12:48:55 by malfwa           ###   ########.fr       */
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
	t_philo		*philo;
	t_action	action[4];
	pthread_t	test;
	// int			i;

	philo = (t_philo *)ptr;
	get_action_tab(action);
	synchronize_launch(philo->table->start);
	pthread_create(&test, NULL, death_routine, philo);
	// if (philo->index % 2 == 0)
	// {
		// my_print(philo, "is thinking");
		// waiting(philo, philo->table->start, philo->table->params.eating);
	// }
	// i = 0;
	// while (!is_death(philo->table) && !are_fed_up(philo->table))
	// {
	// 	if (!action[i])
	// 		i = 0;
	// 	if (!action[i](philo))
	// 		break ;
	// 	i++;
	// }
	pthread_join(test, NULL);
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