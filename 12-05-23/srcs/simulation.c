/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:47:09 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/21 22:05:34 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_struct.h>
#include <philo_time.h>
#include <philo_defines.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

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

	my_print(self, "left eating");
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
	if (philo->index % 2)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		my_print(self, "Has taken a fork");
		pthread_mutex_lock(philo->left_fork_mutex);
	}
	else 
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		my_print(self, "Has taken a fork");
		pthread_mutex_lock(&philo->fork_mutex);
	}
	time_now = get_time_point();
	philo->last_meal = (t_time []){time_now, self->start}[(time_now < self->start)];
	philo->number_of_meal_eaten += 1;
	pthread_mutex_unlock(&self->mutex_philo);
	leave_simulation = wait_for_a_while(self, EAT);
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->fork_mutex);
	if (!leave_simulation)
		return ;
	pthread_mutex_lock(&self->mutex_philo);
	if (philo->number_of_meal_needed != INFINITE \
		&& philo->number_of_meal_eaten == philo->number_of_meal_needed)
	{
		philo->done_eating = true;
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
		usleep(250);
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

void	make_unlink_loop(t_pairs_cursor *lst, bool mode)
{
	t_pairs	*tmp;

	if (!mode)
	{
		lst->current = lst->begin;
		tmp = lst->begin;
		while (tmp->next)
			tmp = tmp->next;
		lst->end = tmp;
		lst->end->next = lst->begin;
		lst->begin->prev = lst->end;
	}
	else
	{
		if (lst->end)
			lst->end->next = NULL;
	}
}

t_pairs	*last_pairs(t_pairs *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_pairs	*copy_listpairs(t_pairs *original)
{
	t_table	table;
	t_pairs	*tmp;

	table = (t_table){0};
	while (original)
	{
		pthread_mutex_lock(&original->mutex_philo);
		if (!add_pairs(&table, original->philo))
			return (free_pairs(table.lst_of_pairs), NULL);
		pthread_mutex_unlock(&original->mutex_philo);
		tmp = last_pairs(table.lst_of_pairs);
		tmp->start = original->start;
		original = original->next;
	}
	return (table.lst_of_pairs);
}

void	pop_pairs(t_pairs_cursor *addr)
{
	t_pairs	*tmp;

	tmp = addr->current;
	
	if (addr->current == addr->current->next)
	{
		addr->begin = NULL;
		addr->current = NULL;
		addr->end = NULL;
	}
	else
	{
		if (addr->current == addr->begin)
			addr->begin = addr->begin->next;
		else if (addr->current == addr->end)
			addr->end = addr->end->prev;
		addr->current->prev->next = addr->current->next;
		addr->current->next->prev = addr->current->prev;
		addr->current = addr->current->next;
	}
	free(tmp);
}

void	join_all(t_pairs *lst)
{
	while (lst)
	{
		pthread_mutex_lock(&lst->mutex_philo);
		pthread_join(lst->philo->thread, NULL);
		pthread_mutex_unlock(&lst->mutex_philo);
		lst = lst->next;
	}
}

void	*supervisor(void *addr)
{
	int		i;
	t_table	*table;
	t_pairs	*tmp;
	t_pairs_cursor	copy;
	pthread_mutex_t	tmp_mutex;

	table = (t_table *)addr;
	tmp = table->lst_of_pairs;
	table->arg = malloc(sizeof(t_pairs) * table->len);
	i = 0;
	while (tmp)
	{
		tmp->print_mutex = table->print_mutex;
		tmp->start = table->departure;
		tmp->philo->last_meal = table->departure;
		table->arg[i] = (t_pairs){tmp->philo, tmp->start, tmp->print_mutex, tmp->mutex_philo, NULL, NULL};
		if (pthread_create(&tmp->philo->thread, NULL, routine, &table->arg[i++]))
			return (set_death(tmp), NULL);
		tmp = tmp->next;
	}
	copy.begin = copy_listpairs(table->lst_of_pairs);
	if (!copy.begin)
		return (write(2, "error malloc\n", 13), NULL);
	make_unlink_loop(&copy, false);
	while (copy.current)
	{
		usleep(200);
		if (is_dead(copy.current))
		{
			make_unlink_loop(&copy, true);
			set_death(copy.current);
			free_pairs(copy.begin);
			break ;
		}
		pthread_mutex_lock(&copy.current->mutex_philo);
		if (copy.current->philo->done_eating)
		{
			tmp_mutex = copy.current->mutex_philo;
			pop_pairs(&copy);
			pthread_mutex_unlock(&tmp_mutex);
		}
		else
		{
			pthread_mutex_unlock(&copy.current->mutex_philo);
			copy.current = copy.current->next;
		}
	}
	join_all(table->lst_of_pairs);
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