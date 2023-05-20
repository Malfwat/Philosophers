/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:47:09 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/20 16:28:00 by malfwa           ###   ########.fr       */
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
		return ;
	return (eat(self));
}

void    philo_sleep(t_philo *self)
{
	bool    leave_simulation;

	leave_simulation = wait_for_a_while(self, SLEEP);
	if (!leave_simulation)
		return ;
	return (think(self));
}
	
void    eat(t_philo *self)
{
	bool    leave_simulation;
	t_time	time_now;

	pthread_mutex_lock(&self->fork_mutex);
	my_print(self, "Has taken a fork");
	pthread_mutex_lock(self->left_fork_mutex);
	time_now = get_time_point();
	self->last_meal = (t_time []){time_now, self->start}[(time_now < self->start)];
	self->number_of_meal_eaten += 1;
	leave_simulation = wait_for_a_while(self, EAT);
	pthread_mutex_unlock(self->left_fork_mutex);
	pthread_mutex_unlock(&self->fork_mutex);
	if (!leave_simulation)
		return ;
	if (self->number_of_meal_needed != INFINITE \
		&& self->number_of_meal_eaten == self->number_of_meal_needed)
		return ;
	return (philo_sleep(self));
}

void	simulation(t_pairs *self)
{
	t_philo	*philo;
	
	pthread_mutex_lock(&self->mutex_philo);
	philo = self->philo;
	if (philo->index % 2)
	{
		pthread_mutex_unlock(&self->mutex_philo);
		usleep(10);
		think(self);
	}
	else
	{
		pthread_mutex_unlock(&self->mutex_philo);
		eat(self);
	}
}

void	*routine(void *addr)
{
	t_pairs *self;

	self = (t_pairs *)addr;
	if (!synchronize_launch(self))
		return (NULL);
	simulation(self);
	return (NULL);
}


void	*supervisor(void *addr)
{
	t_table	*table;
	t_pairs	*tmp;
	int		i;

	i = 0;
	table = (t_table *)addr;
	tmp = table->lst_of_pairs;
	while (tmp)
	{
		tmp->philo->start = table->departure;
		tmp->philo->last_meal = table->departure;
		if (pthread_create(&tmp->philo->thread, NULL, routine, \
			&(t_pairs){tmp->philo, tmp->mutex_philo, NULL}))
			return (set_death(tmp->philo), NULL);
		tmp = tmp->next;
	}

	// make_it_loop
	return (NULL);
}

void	supervise(t_table *table)
{
	pthread_t	supervisor_thread;

	pthread_create(&supervisor_thread, NULL, supervisor, table);
	pthread_join(supervisor_thread, NULL);
}

void    prelaunch(t_table *table)
{
	
	table->departure = get_departure_time(table->len);
	table->p_current = table->p_begin;
	
	supervise(table);
}