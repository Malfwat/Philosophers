/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/23 12:05:55 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_time.h>
#include <philo_defines.h>
#include <philo_structs.h>
#include <stdio.h>
#include <unistd.h>

// void	*thread_print(void *addr)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)addr;
// 	pthread_mutex_lock(philo->table->mutex_print);
// 	printf("%s", str);
// 	pthread_mutex_unlock(philo->table->mutex_print);
// 	return (NULL);
// }

void	think(t_philo *philo);

void	my_print(t_philo *philo, char *str)
{
	t_time	time;

	time = get_timestamp_in_millisec(philo->table->start);
	pthread_mutex_lock(philo->table->mutex_print);
	printf("%-7.03lli %i %s\n", time, philo->index, str);
	pthread_mutex_unlock(philo->table->mutex_print);
}

void	philo_sleep(t_philo *philo)
{
	t_time	time_point;

	time_point = get_time_point();
	while (get_timestamp_in_millisec(time_point) < philo->table->params.sleeping)
	{
		if (philo->table->stop)
			return ;
		// usleep(500);
	}
	think(philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_eating);
	philo->last_meal = get_time_point();
	pthread_mutex_unlock(&philo->mutex_eating);
	if (philo->table->stop)
		return ;
	if (philo->index % 2)
	{
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);
		my_print(philo, "Has taken a fork\n");
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
		my_print(philo, "is eating\n");
	}
	else
	{
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
		my_print(philo, "Has taken a fork\n");
		pthread_mutex_lock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);
		my_print(philo, "is eating\n");	
	}
	while (get_timestamp_in_millisec(philo->last_meal) < philo->table->params.eating)
	{
		// usleep(500);
		if (philo->table->stop)
		{
			pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
			pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);		
			return ;
		}
	}
	pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[LEFT_FORK]]);
	pthread_mutex_unlock(&philo->table->mutex_cutlery[philo->mutex_index[MY_FORK]]);
	my_print(philo, "Dropped\n");
	pthread_mutex_lock(&philo->mutex_eating);
	philo->nb_meal_eaten += 1;
	pthread_mutex_unlock(&philo->mutex_eating);
	if (philo->table->stop)
		return ;
	return (philo_sleep(philo));
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