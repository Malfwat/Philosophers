/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:48:55 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/20 00:35:36 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_struct.h>
#include <string.h>
#include <stdlib.h>

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
		free(table->p_current);
	}
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
	new->number_of_meal_needed = (int []){ft_atoi(av[5]) , -1}[(av[5] == NULL)];
	new->index = index;
	pthread_mutex_init(&new->fork_mutex, NULL);
	return (new);
}

int	add_philo(t_table *table,char **av, int index)
{
	t_philo	*new;

	new = new_philo(av, index);
	if (!new)
		return (2);
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
	return (0);
}

t_table	*create_table(char **av)
{
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_print;
	t_table			*table;
	int				i;
	bool			*boolean;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	pthread_mutex_init(&mutex_stop, NULL);
	pthread_mutex_init(&mutex_print, NULL);
	i = 0;
	table->len = ft_atoi(av[1]);
	while (i++ < table->len)
		if (add_philo(table, av, i))
			return (free_table(table), NULL);
	i = 0;
	boolean = malloc(sizeof(bool));
	if (!boolean)
			return (free_table(table), NULL);
	*boolean = false;	
	while (i++ < table->len)
	{
		table->p_current->stop = boolean;
		table->p_current->mutex_stop = mutex_stop;
		table->p_current->mutex_print = mutex_print;
		table->p_current = table->p_current->next;
	}
	return (table);
}