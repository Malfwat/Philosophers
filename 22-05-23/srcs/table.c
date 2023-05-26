/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:40:57 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/26 19:54:00 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_structs.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	free_table(t_table *table)
{
	int	i;

	if (table->mutex_stop)
	{
		pthread_mutex_destroy(table->mutex_stop);
		free(table->mutex_stop);
	}
	if (table->mutex_print)
	{
		pthread_mutex_destroy(table->mutex_print);
		free(table->mutex_print);
	}
	if (table->mutex_cutlery)
	{
		i = 0;
		while (i < table->params.nb_of_philo)
			pthread_mutex_destroy(&table->mutex_cutlery[i++]);
		free(table->mutex_cutlery);
	}
	free(table);
}

t_table	*create_table(int ac, char **av)
{
	t_table		*table;
	int			i;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (write(2, "Error malloc\n", 13), NULL);
	if (!init_params(&table->params, ac, av))
		return (NULL);
	table->mutex_stop = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!table->mutex_stop || pthread_mutex_init(table->mutex_stop, NULL))
		return (write(2, "Error malloc\n", 13), NULL);
	table->mutex_print = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!table->mutex_print || pthread_mutex_init(table->mutex_print, NULL))
		return (free_table(table), write(2, "Error malloc\n", 13), NULL);
	table->mutex_cutlery = ft_calloc(1, sizeof(pthread_mutex_t) * (table->params.nb_of_philo + 1));
	if (!table->mutex_cutlery)
		return (free_table(table), write(2, "Error malloc\n", 13), NULL);
	i = 0;
	while (i < table->params.nb_of_philo)
	{
		if (pthread_mutex_init(&table->mutex_cutlery[i++], NULL))
			return (free_table(table), NULL);
	}
	return (table);
}

void	free_supervisor(t_supervisor *ptr)
{
	if (!ptr)
		return ;
	if (ptr->table)
		free_table(ptr->table);
	if (ptr->philo_tab)
		free(ptr->philo_tab);
	free(ptr);
}

bool	fill_philo_tab(t_table *table, t_philo *tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (i == size - 1)
			tab[i].mutex_index[RIGHT_FORK] = 0;
		else
			tab[i].mutex_index[RIGHT_FORK] = i + 1;
		tab[i].mutex_index[MY_FORK] = i;
		tab[i].index = i + 1;
		printf("philo: %i, mutxtab:[%i][%i]\n", tab[i].index, tab[i].mutex_index[MY_FORK], tab[i].mutex_index[RIGHT_FORK]);
		tab[i].table = table;
		if (pthread_mutex_init(&tab[i].mutex_eating, NULL))
			return (false);
	}
	return (true);
}

t_supervisor	*create_supervisor(t_table *table)
{
	t_supervisor	*supervisor;

	supervisor = ft_calloc(1, sizeof(t_supervisor));
	if (!supervisor)
		return (free_table(table), NULL);
	supervisor->table = table;
	supervisor->philo_tab = ft_calloc(table->params.nb_of_philo + 1, sizeof(t_philo));
	if (!supervisor->philo_tab)
		return (free_supervisor(supervisor), NULL);
	if (!fill_philo_tab(table, supervisor->philo_tab, table->params.nb_of_philo))
		return (free_supervisor(supervisor), NULL);
	return (supervisor);
}