/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/24 13:27:27 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_time.h>
#include <philo_defines.h>
#include <philo_structs.h>
#include <stdio.h>
#include <philosophers.h>
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

void	*routine(void	*ptr)
{
	t_time	time;
	t_philo	*philo;

	philo = (t_philo *)ptr;
	synchronize_launch(philo->table->start);
	time = get_timestamp_in_millisec(philo->table->start);
	return (NULL);
	if (philo->index % 2)
		think(philo);
	else
		eat(philo);
	return (NULL);
}

void	set_end(t_table *table)
{
	pthread_mutex_lock(table->mutex_stop);
	table->stop = true;
	pthread_mutex_unlock(table->mutex_stop);
}

bool	is_dead(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_eating);
	if (get_timestamp_in_millisec(philo->last_meal) > table->params.dying)
	{
		my_print(philo, "is dead");
		set_end(table);
		pthread_mutex_unlock(&philo->mutex_eating);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex_eating);
	return (false);
}

void	check_end(t_supervisor *supervisor)
{
	int i;
	int	done_eating;

	done_eating = 0;
	i = 0;
	while (1)
	{
		if (done_eating == supervisor->table->params.nb_of_philo)
			return (set_end(supervisor->table));
		if (i == supervisor->table->params.nb_of_philo)
			i = 0;
		if (is_dead(supervisor->table, &supervisor->philo_tab[i]))
			return ;
		if (supervisor->philo_tab[i].nb_meal_eaten == supervisor->table->params.nb_of_meal_needed)
			done_eating++;
		i++;
	}	
}

void	simulation(t_supervisor *supervisor)
{
	int	i;

	i = -1;
	supervisor->table->start = get_departure_time(supervisor->table->params.nb_of_philo);
	while (++i < supervisor->table->params.nb_of_philo)
		supervisor->philo_tab[i].last_meal = supervisor->table->start;
	i = -1;
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_create(&supervisor->philo_tab[i].thread, NULL, routine, &supervisor->philo_tab[i]);
	i = -1;
	check_end(supervisor);
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_join(supervisor->philo_tab[i].thread, NULL);
}