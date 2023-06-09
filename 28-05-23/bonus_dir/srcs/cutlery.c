/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutlery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:43:08 by malfwa            #+#    #+#             */
/*   Updated: 2023/06/09 22:27:30 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher_bonus.h>
#include <philo_bonus_time.h>
#include <philo_bonus_struct.h>
#include <semaphore.h>

void	drop_cutlery(sem_t *cutlery)
{
	sem_post(cutlery);
	sem_post(cutlery);
}

bool	get_cutlery(t_philo *philo)
{
	sem_wait(philo->sem_to_take);
	sem_wait(philo->cutlery);
	if (is_dead(philo) || is_death(philo))
	{
		sem_post(philo->cutlery);
		sem_post(philo->sem_to_take);
		return (false);
	}
	my_print(philo, "has taken a fork");
	if (philo->params.nb_philo == 1)
	{
		sem_post(philo->cutlery);
		waiting(philo, philo->start, philo->params.dying + 1);
		sem_post(philo->sem_to_take);
		return (is_dead(philo), false);
	}
	sem_wait(philo->cutlery);
	sem_post(philo->sem_to_take);
	if (is_dead(philo) || is_death(philo))
		return (drop_cutlery(philo->cutlery), false);
	philo->last_meal = get_time_point();
	return (true);	
}