/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:54:23 by malfwa            #+#    #+#             */
/*   Updated: 2023/03/27 18:21:27 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_philo	*new_philo(pthread_mutex_t *mutex, char **av, int index)
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
	new->mutex = mutex;
	pthread_mutex_init(&new->fork_mutex, NULL);
	return (new);
}

int	add_philo(pthread_mutex_t *mutex, t_table *table,char **av, int index)
{
	t_philo	*new;

	new = new_philo(mutex, av, index);
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

t_table	*create_table(char **av, pthread_mutex_t *mutex)
{
	t_table	*new;
	int		i;
	bool	*boolean;
	
	(void)mutex;
	new = malloc(sizeof(t_table));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_table));
	i = 0;
	new->len = ft_atoi(av[1]);
	while (i++ < new->len)
		if (add_philo(mutex, new, av, i))
			return (free_table(new), NULL);
	i = 0;
	boolean = malloc(sizeof(bool));
	memset(boolean, 0, sizeof(bool));
	while (i++ < new->len)
	{
		new->p_current->stop = boolean;
		new->p_current = new->p_current->next;
	}
	return (new);
}
