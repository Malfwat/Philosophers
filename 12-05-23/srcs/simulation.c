/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:47:09 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/16 19:40:47 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_struct.h>
#include <philo_time.h>

void    eat(t_philo *self)
{
    pthread_mutex_lock(&self->fork_mutex);
    pthread_mutex_lock(self->left_fork_mutex);
    printf("%-7.03lli %i Has taken a fork\n", get_timestamp_in_millisec(self->start), self->index);
    self->last_meal = get_time_point();
    wait_for_a_while(self, EAT);
    pthread_mutex_unlock(self->left_fork_mutex);
    pthread_mutex_unlock(&self->fork_mutex);
}

void    simulation(t_philo *self)
{
    if (self->index % 2)
        usleep(100);
    eat(self);
}

void    routine(void *addr)
{
    t_philo *philo;

    philo = (t_philo *)addr;
    synchronize_launch(philo->start);
    simulation(philo);
}

void    prelaunch(t_table table)
{
    int     i;
    t_time  departure;
    
    i = 0;
    departure = get_departure_time(table.len);
    while (!i++ || table.p_current != table.p_begin)
    {
        table.p_current->start = departure;
        pthread_create(&table.p_current->thread, NULL, routine, table.p_current);
        table.p_current = table.p_current->next;
    }
}