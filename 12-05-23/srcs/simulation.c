/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:47:09 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/21 00:21:38 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_struct.h>
#include <philo_time.h>
#include <philo_defines.h>
#include <unistd.h>
#include <stdlib.h>

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
	// if (philo->index % 2)
	// {
		pthread_mutex_lock(&philo->fork_mutex);
		my_print(self, "Has taken a fork");
		pthread_mutex_lock(philo->left_fork_mutex);
	// }
	// else 
	// {
		// pthread_mutex_lock(philo->left_fork_mutex);
		// my_print(self, "Has taken a fork");
		// pthread_mutex_lock(&philo->fork_mutex);
	// }
	time_now = get_time_point();
	philo->last_meal = (t_time []){time_now, self->start}[(time_now < self->start)];
	philo->number_of_meal_eaten += 1;
	pthread_mutex_unlock(&self->mutex_philo);
	leave_simulation = wait_for_a_while(self, EAT);
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->fork_mutex);
	if (!leave_simulation)
	{
		printf("je quitte ici\n");
		return ;
	}
	pthread_mutex_lock(&self->mutex_philo);
	if (philo->number_of_meal_needed != INFINITE \
		&& philo->number_of_meal_eaten == philo->number_of_meal_needed)
	{
		my_print(self, "done_eating");
		philo->done_eating = true;
		pthread_mutex_unlock(&self->mutex_philo);
		printf("je quitdte ici\n");
		return ;
	}
	pthread_mutex_unlock(&self->mutex_philo);
		printf("je quittse ici\n");
	
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

void	make_unlink_loop(t_pairs *lst, bool mode)
{
	t_pairs *begin;
	static t_pairs *end;

	if (!mode)
	{
		begin = lst;
		while (lst->next)
			lst = lst->next;
		end = lst;
		lst->next = begin;
	}
	else
	{
		if (end)
			end->next = NULL;
	}
}

t_pairs	*copy_listpairs(t_pairs *original)
{
	t_table	table;

	table = (t_table){0};
	while (original)
	{
		add_pairs(&table, original->philo);
		original = original->next;
	}
	return (table.lst_of_pairs);
}

void	pop_pairs(t_pairs **addr)
{
	t_pairs	*tmp;

	tmp = *addr;
	
	printf("je passe\n");
	if (tmp == tmp->next)
		*addr = NULL;
	else
	{
		(*addr)->prev->next = (*addr)->next;
		(*addr) = (*addr)->next;
	}
	free(tmp);
}

void	*supervisor(void *addr)
{
	int		i;
	t_table	*table;
	t_pairs	*tmp;
	t_pairs	*copy;

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
	copy = copy_listpairs(table->lst_of_pairs);
	make_unlink_loop(copy, false);
	while (copy)
	{
		usleep(200);
		if (is_dead(copy))
			return (make_unlink_loop(NULL, true), /* set_death(copy), */ NULL);
		pthread_mutex_lock(&copy->mutex_philo);
		if (copy->philo->done_eating)
		{
			pop_pairs(&copy);
			pthread_mutex_unlock(&copy->mutex_philo);
		}
		else
		{
			pthread_mutex_unlock(&copy->mutex_philo);
			copy = copy->next;
		}
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