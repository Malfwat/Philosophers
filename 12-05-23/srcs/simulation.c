/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:47:09 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/20 18:35:13 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_struct.h>
#include <philo_time.h>
#include <philo_defines.h>
#include <unistd.h>

void    eat(t_pairs *self);


void	think(t_pairs *self)
{
	int	leave_simulation;

	leave_simulation = wait_for_a_while(self, THINK);
	if (!leave_simulation)
		return ;
	return (eat(self));
}

void    philo_sleep(t_pairs *self)
{
	bool    leave_simulation;

	leave_simulation = wait_for_a_while(self, SLEEP);
	if (!leave_simulation)
		return ;
	return (think(self));
}
	
void    eat(t_pairs *self)
{
	bool    leave_simulation;
	t_time	time_now;
	t_philo	*philo;

	pthread_mutex_lock(&self->mutex_philo);
	philo = self->philo;
	pthread_mutex_lock(&philo->fork_mutex);
	my_print(self, "Has taken a fork");
	pthread_mutex_lock(philo->left_fork_mutex);
	time_now = get_time_point();
	philo->last_meal = (t_time []){time_now, self->start}[(time_now < self->start)];
	philo->number_of_meal_eaten += 1;
	leave_simulation = wait_for_a_while(self, EAT);
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->fork_mutex);
	if (!leave_simulation)
	{
		pthread_mutex_unlock(&self->mutex_philo);
		return ;
	}
	if (philo->number_of_meal_needed != INFINITE \
		&& philo->number_of_meal_eaten == philo->number_of_meal_needed)
	{
		pthread_mutex_unlock(&self->mutex_philo);
		return ;
	}
	pthread_mutex_unlock(&self->mutex_philo);
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

void	make_it_loop(t_pairs *lst)
{
	t_pairs *begin;

	begin = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = begin;
}

void	*supervisor(void *addr)
{
	t_table	*table;
	t_pairs	*tmp;
	t_pairs	*arg;

	table = (t_table *)addr;
	tmp = table->lst_of_pairs;
	while (tmp)
	{
		tmp->print_mutex = table->print_mutex;
		tmp->start = table->departure;
		tmp->philo->last_meal = table->departure;
		arg = &(t_pairs){tmp->philo, tmp->start, tmp->print_mutex, tmp->mutex_philo, NULL};
		if (pthread_create(&tmp->philo->thread, NULL, routine, arg))
			return (set_death(tmp), NULL);
		tmp = tmp->next;
	}
	make_it_loop(table->lst_of_pairs);
	while (table->lst_of_pairs)
	{
		if (is_dead(table->lst_of_pairs))
			return (set_death(table->lst_of_pairs), NULL);
		table->lst_of_pairs = table->lst_of_pairs->next;
	}
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