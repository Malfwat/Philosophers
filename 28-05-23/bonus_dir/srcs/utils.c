/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:46:28 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/12 18:29:30 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <philosopher_bonus.h>
#include <philo_bonus_struct.h>
#include <philo_bonus_time.h>

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

bool	is_dead(t_philo *philo)
{
	t_time	time_to_die;
	t_time	time_point;

	time_to_die = philo->params.dying;
	time_point = philo->last_meal;
	if (get_timestamp_in_millisec(time_point) > time_to_die)
	{
		my_print(philo, "died");
		return (set_death(philo));
	}
	return (false);
}

void	incremt_sem(sem_t *sem, int count_to_add)
{
	int	i;

	i = 0;
	while (i++ < count_to_add)
		sem_post(sem);
}

bool	set_death(t_philo *philo)
{
	incremt_sem(philo->supervise.sem_death, philo->params.nb_philo);
	return (true);
}

bool	is_death(t_philo *philo)
{
	bool	exit_value;

	pthread_mutex_lock(&philo->supervise.stop_mutx);
	exit_value = philo->supervise.stop;
	pthread_mutex_unlock(&philo->supervise.stop_mutx);
	return (exit_value);
}
