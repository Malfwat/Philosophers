/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:19:13 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/31 14:51:24 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus_struct.h>
#include <philosopher_bonus.h>
#include <philo_bonus_defines.h>
#include <stdbool.h>

void	free_philo(t_philo *philo)
{
	if (!philo)
		return ;
	close_sem(philo->supervise.sem_fed, SEM_FED);
	close_sem(philo->supervise.sem_death, SEM_DEATH);
	free_cutlery(philo->cutlery, philo->sem_names);
	free_tab(sem_names);
	free(philo);
}

bool	init_t_over(t_over *supervise, int nb_philo)
{
	if (!init_sem(&supervise->sem_death, SEM_DEATH, 0))
		return (free(new), false);
	if (!init_sem(&supervise->sem_fed, SEM_FED, nb_philo))
		return (close_sem(supervise->sem_fed, SEM_FED), free(new), false);
	if (phread_mutex_init(&supervise->stop, NULL))
	{
		close_sem(supervise->sem_fed, SEM_FED);
		close_sem(supervise->sem_death, SEM_DEATH);
		return (false);
	}
	return (true);
}

t_philo	*create_philo(int ac, char **av)
{
	t_philo	*new;

	new = ft_calloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	if (!init_params(&new->params, ac, av))
		return (free(new), NULL);
	if (!init_over(&new->supervisor, new->params.nb_philo))
		return (free(new), NULL);
	if (!create_cutlery(&new->cutlery, new->params.nb_philo))
		return (free_philo(new));
	return (new);
}
