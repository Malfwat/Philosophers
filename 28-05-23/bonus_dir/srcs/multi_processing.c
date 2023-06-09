/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:38:46 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/09 21:57:43 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus_struct.h>
#include <philo_bonus_time.h>
#include <philosopher_bonus.h>

////////////////// in a thread ///////////////////////

void	*check_death_ending(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	sem_wait(philo->supervise.sem_death);
	pthread_mutex_lock(&philo->supervise.stop_mutx);
	philo->supervise.stop = true;
	pthread_mutex_unlock(&philo->supervise.stop_mutx);
	return (NULL);
}

//////////////////////////////////////////////////////

///////////////// in another thread //////////////////

void	*are_fed_up(void *ptr)
{
	int	i;
	t_philo	*philo;

	philo = (t_philo *)ptr;
	i = 0;
	while (i < philo->params.nb_philo)
		sem_wait(philo->supervise.sem_fed[i++]);
	pthread_mutex_lock(&philo->supervise.stop_mutx);
	philo->supervise.stop = true;
	pthread_mutex_unlock(&philo->supervise.stop_mutx);
	return (NULL);
}

//////////////////////////////////////////////////////
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