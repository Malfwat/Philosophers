/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:47:09 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/17 19:16:18 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_struct.h>
#include <philo_time.h>
#include <philo_defines.h>
#include <unistd.h>

void    eat(t_philo *self);


void	think(t_philo *self)
{
	int	leave_simulation;

	leave_simulation = wait_for_a_while(self, THINK);
	if (!leave_simulation)
		exit ;
	return (eat(self));
}

void    philo_sleep(t_philo *self)
{
	bool    leave_simulation;

	leave_simulation = wait_for_a_while(self, SLEEP);
	if (!leave_simulation)
		exit ;
	return (think(self));
}
	
void    eat(t_philo *self)
{
	bool    leave_simulation;

	pthread_mutex_lock(&self->fork_mutex);
	pthread_mutex_lock(self->left_fork_mutex);
	self->last_meal = get_time_point();
	leave_simulation = wait_for_a_while(self, EAT);
	pthread_mutex_unlock(self->left_fork_mutex);
	pthread_mutex_unlock(&self->fork_mutex);
	if (!leave_simulation)
		exit ;
	return (philo_sleep(self));
}

void	simulation(t_philo *self)
{
	if (self->index % 2)
	{
		usleep(100);
		think(self);
	}
	eat(self);
}

void	*routine(void *addr)
{
	t_philo *philo;

	philo = (t_philo *)addr;
	synchronize_launch(philo->start);
	simulation(philo);
	return (NULL);
}

void    prelaunch(t_table table)
{
	int     i;
	t_time  departure;
	
	i = 0;
	departure = get_departure_time(table.len);
	// table.p_current = table.p_begin;
	while (!i++ || table.p_current != table.p_begin)
	{
		table.p_current->start = departure;
		table.p_current->last_meal = departure;
		pthread_create(&table.p_current->thread, NULL, routine, table.p_current);
		table.p_current = table.p_current->next;
	}
	i = 0;
	while (table.p_current != table.p_begin || !i++)
	{
		pthread_join(table.p_current->thread, NULL);
		table.p_current = table.p_current->next;
	}
}