/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:40:57 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/22 16:58:43 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_structs.h>
#include <stdbool.h>
#include <string.h>


#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	max_int;
	char	*tmp;
	size_t	i;
	size_t	value_asked;

	max_int = INT_MAX;
	i = 0;
	if (nmemb == 0 || size == 0)
	{
		tmp = malloc(sizeof(char));
		if (tmp)
			tmp[0] = 0;
		return ((void *)tmp);
	}
	if (nmemb > max_int / size || size > max_int / nmemb)
		return (NULL);
	value_asked = nmemb * size;
	tmp = malloc((value_asked));
	if (tmp == NULL)
		return (NULL);
	while (i < value_asked)
		tmp[i++] = 0;
	return ((void *)tmp);
}


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
		while (table->mutex_cutlery[i])
			pthread_mutex_destroy(table->mutex_cutlery[i++]);
		free(table->mutex_cutlery);
	}
}

t_table	*create_table(int ac, char **av)
{
	t_table		*table;
	int			i;

	table = ft_calloc(1, sizeof(t_table))
	if (!table)
		return (write(2, "Error malloc\n", 13), NULL);
	if (!init_params(&table.params, ac, av))
		return (NULL);
	table->mutex_stop = ft_calloc(sizeof(pthread_mutex_t));
	if (!table->mutex_stop)
		return (write(2, "Error malloc\n", 13), NULL);
	table->mutex_print = ft_calloc(sizeof(pthread_mutex_t));
	if (!table->mutex_print)
		return (free_table(table), write(2, "Error malloc\n", 13), NULL);
	table->mutex_cutlery = ft_calloc(sizeof(pthread_mutex_t) * table->params->nb_of_philo);
	if (!table->mutex_cutlery)
		return (free_table(table), write(2, "Error malloc\n", 13), NULL);
	i = 0;
	while (table->mutex_cutlery[i])
	{
		if (!pthread_mutex_init(table->mutex_cutlery[i++]))
			return (free_table(table), NULL);
	}
	return (table);
}