/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/22 20:49:48 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_time.h>
#include <philo_defines.h>
#include <philo_structs.h>
#include <stdio.h>


void	my_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->table->mutex_print);
	printf("%s", str);
	pthread_mutex_unlock(philo->table->mutex_print);
}

void	*routine(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	(void)philo;
	synchronize_launch(philo->table->start);
	my_print(philo, "oui\n");
	return (NULL);
}

void	simulation(t_supervisor *supervisor)
{
	int	i;

	i = -1;
	supervisor->table->start = get_departure_time(supervisor->table->params.nb_of_philo);
	while (++i < supervisor->table->params.nb_of_philo)
	{
		pthread_create(&supervisor->philo_tab[i].thread, NULL, routine, &supervisor->philo_tab[i]);
	}
	i = -1;
	while (++i < supervisor->table->params.nb_of_philo)
	{
		pthread_join(supervisor->philo_tab[i].thread, NULL);
	}
	printf("out\n");
}