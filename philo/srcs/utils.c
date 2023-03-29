/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:43:23 by malfwa            #+#    #+#             */
/*   Updated: 2023/03/27 18:21:03 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void    free_table(t_table *table)
{
	if (!table)
		return ;
	table->p_end->next = NULL;
	while (table->p_begin)
	{
		table->p_current = table->p_begin;
		table->p_begin = table->p_begin->next;
		pthread_mutex_destroy(&table->p_current->fork_mutex);
		free(table->p_current);
	}
	free(table);
}

static bool	ft_is_digit(char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

bool	is_good_params(int ac, char **av)
{
	short	i;
	int		x;

	if (ac != 6 && ac != 5)
		return (false);
	i = 1;
	while (av[i])
	{
		x = 0;
		while (av[i][x])
		{
			if (ft_is_digit(av[i][x]) == false)
				return (false);
			x += 1;
		}
		i += 1;
	}
	return (true);
}