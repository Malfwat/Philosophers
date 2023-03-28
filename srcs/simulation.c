/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:36:07 by amouflet          #+#    #+#             */
/*   Updated: 2023/03/27 18:47:10 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	sleeping(t_philo *self, unsigned long long time)
{
	return (eat(self));
}

void	eat(t_philo *self)
{
	unsigned long long	time;
	
	printf("%-7.03lli %i start thinking\n", \
	time, \
	self->index);
	
	return (sleeping(self, time));
}

void    simulation(t_philo *self)
{
	
}

void    *routine(void *tmp)
{
	t_philo *self;

	self = (t_philo *)tmp;
	while (get_actual_time() < self->start)
		continue ;
	simulation(self);
	return (NULL);
}

void    first_launch(t_table *table)
{
	unsigned long long  start;
	unsigned long long  actual;
	bool                go;

	start = (get_actual_time() + 1200 * table->len);
	actual = (unsigned long long)0;
	go = true;
	while (table->p_current != table->p_begin || go == true)
	{
		table->p_current->start = start;
		table->p_current->actual_time = actual;
		go = false;
		pthread_create(&table->p_current->thread, NULL, routine, table->p_current);
		table->p_current = table->p_current->next;
	}
	go = true;
	while (table->p_current != table->p_begin || go == true)
	{
		pthread_join(table->p_current->thread, NULL);
		table->p_current = table->p_current->next;
		go = false;
	}
}