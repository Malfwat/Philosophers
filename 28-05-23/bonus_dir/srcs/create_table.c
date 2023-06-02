/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:19:13 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/02 17:01:26 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus_struct.h>
#include <philosopher_bonus.h>
#include <philo_bonus_defines.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

void	free_philo(t_philo *philo)
{
	if (!philo)
		return ;
	close_sem(philo->supervise.sem_fed, SEM_FED);
	close_sem(philo->supervise.sem_death, SEM_DEATH);
	close_sem(philo->supervise.sem_death, SEM_CUTLERY);
	free(philo);
}

void	close_t_over(t_over *supervise)
{
	close_sem(supervise->sem_fed, SEM_FED);
	close_sem(supervise->sem_death, SEM_DEATH);
}

bool	init_t_over(t_over *supervise)
{
	if (!init_sem(&supervise->sem_death, SEM_DEATH, 0))
		return (false);
	if (!init_sem(&supervise->sem_fed, SEM_FED, 0))
		return (close_sem(supervise->sem_death, SEM_DEATH), false);
	if (pthread_mutex_init(&supervise->stop, NULL))
		return (close_t_over(supervise), false);
	return (true);
}

t_philo	*create_philo(int ac, char **av)
{
	t_philo	*new;

	new = ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	if (!init_params(&new->params, ac, av))
		return (free(new), NULL);
	if (!init_t_over(&new->supervise))
		return (free(new), NULL);
	if (!init_sem(&new->cutlery, SEM_CUTLERY, new->params.nb_philo))
		return (close_t_over(&new->supervise), free(new), NULL);
	return (new);
}
