/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:00:34 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/23 23:14:49 by malfwa           ###   ########.fr       */
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
	my_print(philo, "test", time);
	// if (philo->index % 2)
	// 	think(philo);
	// else
	// 	eat(philo);
	return (NULL);
}

// void	check_end(t_supervisor *supervisor)
// {
// 	int i;
// 	int	done_eating;

// 	done_eating = 0;
// 	i = 0;
// 	while (1)
// 	{
// 		if (done_eating == supervisor->table->params.nb_of_philo)
// 		{
// 			pthread_mutex_lock(supervisor->table->mutex_stop);
// 			supervisor->table->stop = true;
// 			pthread_mutex_unlock(supervisor->table->mutex_stop);
// 			return ;
// 		}
// 		if (i == supervisor->table->params.nb_of_philo)
// 		{
// 			i = 0;
// 			done_eating = 0;
// 		}
// 		if (supervisor->philo_tab[i].last_meal >= supervisor->table->start)
// 		{
// 			if (get_timestamp_in_millisec(supervisor->philo_tab[i].last_meal) > supervisor->table->params.dying)
// 			{
// 				my_print(&supervisor->philo_tab[i], "is dead");
// 				pthread_mutex_lock(supervisor->table->mutex_stop);
// 				supervisor->table->stop = true;
// 				pthread_mutex_unlock(supervisor->table->mutex_stop);
// 				return ;
// 			}
// 		}
// 		if (supervisor->philo_tab[i].nb_meal_eaten == supervisor->table->params.nb_of_meal_needed)
// 			done_eating++;
// 		i++;
// 	}	
// }

void	simulation(t_supervisor *supervisor)
{
	int	i;

	i = -1;
	supervisor->table->start = get_departure_time(supervisor->table->params.nb_of_philo);
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_create(&supervisor->philo_tab[i].thread, NULL, routine, &supervisor->philo_tab[i]);
	i = -1;
	// check_end(supervisor);
	while (++i < supervisor->table->params.nb_of_philo)
		pthread_join(supervisor->philo_tab[i].thread, NULL);
}