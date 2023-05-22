/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/23 00:36:28 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_time.h>
#include <philo_defines.h>
#include <philo_structs.h>
#include <stdio.h>

// void	*thread_print(void *addr)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)addr;
// 	pthread_mutex_lock(philo->table->mutex_print);
// 	printf("%s", str);
// 	pthread_mutex_unlock(philo->table->mutex_print);
// 	return (NULL);
// }

void	my_print(t_philo *philo, char *str)
{
	t_time	time;

	time = get_timestamp_in_millisec(philo->table->start);
	pthread_mutex_lock(philo->table->mutex_print);
	printf("%-7.03lli %i %s\n", time, philo->index, str);
	pthread_mutex_unlock(philo->table->mutex_print);
}

void	eat(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(philo->table->mutex_cutlery[philo->mutex_index])
	}
	else
	{
		
	}
	my_print(philo, "Has taken a fork\n");
}

void	think(t_philo *philo)
{
	if (philo->table->stop)
		return ;
	my_print(philo, "is thinking\n");
	return (eat(philo));
}

void	*routine(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	(void)philo;
	synchronize_launch(philo->table->start);
	if (philo->index % 2)
	{
		usleep(35);
		think(philo);
	}
	else
		eat(philo);
	return (NULL);
}

void	simulation(t_supervisor *supervisor)
{
	int	i;

	i = -1;
	supervisor->table->start = get_departure_time(supervisor->table->params.nb_of_philo);
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_create(&supervisor->philo_tab[i].thread, NULL, routine, &supervisor->philo_tab[i]);
	i = -1;
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_join(supervisor->philo_tab[i].thread, NULL);
	printf("out\n");
}