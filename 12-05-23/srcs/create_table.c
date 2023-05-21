/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:48:55 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/21 11:51:40 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_struct.h>
#include <string.h>
#include <stdlib.h>

void	free_pairs(t_pairs *pairs)
{
	t_pairs	*tmp;
	
	while (pairs)
	{
		tmp = pairs;
		pairs = pairs->next;
		free(tmp);
	}
}

void    free_table(t_table *table)
{
	if (!table)
		return ;
	table->p_end->next = NULL;
	free(table->p_begin->stop);
	while (table->p_begin)
	{
		table->p_current = table->p_begin;
		table->p_begin = table->p_begin->next;
		pthread_mutex_destroy(&table->p_current->fork_mutex);
		pthread_mutex_destroy(&table->p_current->self_mutex);
		free(table->p_current);
	}
	free_pairs(table->lst_of_pairs_begin);
	free(table->arg);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	free(table);
}

t_philo	*new_philo(char **av, int index)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	new->time_to_die = ft_atoi(av[2]);
	new->time_to_eat = ft_atoi(av[3]);
	new->time_to_sleep = ft_atoi(av[4]);
	new->number_of_meal_needed = (int []){ft_atoi(av[5]) , INFINITE}[(av[5] == NULL)];
	new->index = index;
	pthread_mutex_init(&new->fork_mutex, NULL);
	pthread_mutex_init(&new->self_mutex, NULL);
	return (new);
}

t_pairs	*new_pairs(t_philo *philo)
{
	t_pairs	*new;
	
	new = malloc(sizeof(t_pairs));
	if (!new)
		return (new);
	memset(new, 0, sizeof(t_pairs));
	new->mutex_philo = philo->self_mutex;
	new->philo = philo;
	return (new);
}

bool	add_pairs(t_table *table, t_philo *philo)
{
	t_pairs	*new;
	t_pairs	*tmp;

	new = new_pairs(philo);
	if (!new)
		return (false);
	if (!table->lst_of_pairs)
		table->lst_of_pairs = new;
	else
	{
		tmp = table->lst_of_pairs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (true);
}

bool	add_philo(t_table *table, char **av, int index)
{
	t_philo	*new;

	new = new_philo(av, index);
	if (!new || !add_pairs(table, new))
		return (free(new), false);
	if (!table->p_begin)
	{
		table->p_begin = new;
		table->p_current = new;
		table->p_end = new;
	}
	else
	{
		new->prev = table->p_end;
		table->p_end->next = new;
		table->p_begin->left_fork_mutex = &new->fork_mutex;
		new->left_fork_mutex = &table->p_end->fork_mutex;
		table->p_end = new;
	}
	table->p_begin->prev = table->p_end;
	new->next = table->p_begin;
	return (true);
}

t_table	*create_table(char **av)
{
	t_table			*table;
	int				i;
	bool			*boolean;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	i = 0;
	table->len = ft_atoi(av[1]);
	while (i++ < table->len)
		if (!add_philo(table, av, i))
			return (free_table(table), NULL);
	i = 0;
	boolean = malloc(sizeof(bool));
	if (!boolean)
			return (free_table(table), NULL);
	*boolean = false;
	table->lst_of_pairs_begin = table->lst_of_pairs;
	while (i++ < table->len)
	{
		table->p_current->stop = boolean;
		table->p_current->stop_mutex = table->stop_mutex;
		table->p_current = table->p_current->next;
	}
	return (table);
}
