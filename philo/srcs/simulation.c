/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:36:07 by amouflet          #+#    #+#             */
/*   Updated: 2023/03/29 03:24:36 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

bool	check_stop_bool(t_philo	*self)
{
	bool	return_value;
	
	pthread_mutex_lock(self->mutex);
	return_value = *self->stop;
	pthread_mutex_unlock(self->mutex);
	return (return_value);
}

bool	is_starved(t_philo *self)
{
	unsigned long long	time = gettime(self->last_meal);
	if (time > self->time_to_die)
	{
		printf("%-7.03lli %i Died\n", gettime(self->start), self->index);
		return (printf("sdfsdgd %lli", time), true);
	}
	return (false);
}

void	sleeping(t_philo *self)
{
	unsigned long long tmp;
	
	printf("%-7.03lli %i start sleeping\n", gettime(self->start), self->index);
	tmp = get_actual_time();
	while (gettime(tmp) < self->time_to_sleep)
	{
		if (check_stop_bool(self))
			return ;
	}
	return (eat(self));
}

void	eat(t_philo *self)
{
	printf("%-7.03lli %i start thinking\n", gettime(self->start), self->index);
	pthread_mutex_lock(self->left_fork_mutex);
	printf("%-7.03lli %i has taken a fork\n", gettime(self->start), self->index);
	pthread_mutex_lock(&self->fork_mutex);
	printf("%-7.03lli %i has taken a fork\n", gettime(self->start), self->index);
	self->last_meal = get_actual_time();
	if (check_stop_bool(self))
		return ;
	printf("%-7.03lli %i start eating\n", gettime(self->start), self->index);
	while (gettime(self->last_meal) < self->time_to_eat)
	{
		if (check_stop_bool(self))
			return ;
	}
	self->number_of_meal_eaten += 1;
	pthread_mutex_unlock(self->left_fork_mutex);
	pthread_mutex_unlock(&self->fork_mutex);
	return (sleeping(self));
}

bool	is_finished(t_table *table)
{
	t_philo	*tmp;
	bool	go;

	go = true;
	tmp = table->p_begin;
	while (go || tmp != table->p_begin)
	{
		go = false;
		if (tmp->number_of_meal_needed >= tmp->number_of_meal_eaten)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

void	ending_simulation(t_table *table)
{
	t_philo	*tmp;
	bool	go;

	go = true;
	tmp = table->p_begin;
	pthread_mutex_lock(tmp->mutex);
	*tmp->stop = true;
	pthread_mutex_unlock(tmp->mutex);
	while (go || tmp != table->p_begin)
	{
		go = false;
		pthread_mutex_unlock(&tmp->fork_mutex);
		tmp = tmp->next;
	}
}

void    *supervisor(void *tmp)
{
	t_table	*table;

	table = (t_table *)tmp;
	while (get_actual_time() < table->p_current->start)
		continue ;
	while (table->p_current->number_of_meal_needed == -1 || !is_finished(table))
	{
		if (is_starved(table->p_current))
			return (ending_simulation(table), NULL);
		table->p_current = table->p_current->next;
	}
	return (NULL);
}

void    *routine(void *tmp)
{
	t_philo *self;

	self = (t_philo *)tmp;
	while (get_actual_time() < self->start)
		continue ;
	if (self->index % 2 == 0)
		usleep(50);
	eat(self);
	return (NULL);
}

void    first_launch(t_table *table)
{
	pthread_t			supervise;
	unsigned long long  start;
	unsigned long long  actual;
	bool                go;

	start = (get_actual_time() + 12000 * table->len);
	actual = (unsigned long long)0;
	go = true;
	while (table->p_current != table->p_begin || go == true)
	{
		table->p_current->start = start;
		table->p_current->last_meal = start;
		table->p_current->actual_time = actual;
		go = false;
		pthread_create(&table->p_current->thread, NULL, routine, table->p_current);
		table->p_current = table->p_current->next;
	}
	go = true;
	pthread_create(&supervise, NULL, supervisor, table);
	pthread_join(supervise, NULL);
	while (table->p_current != table->p_begin || go == true)
	{
		pthread_join(table->p_current->thread, NULL);
		table->p_current = table->p_current->next;
		go = false;
	}
}