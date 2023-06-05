/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:19:13 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/05 18:36:23 by malfwa           ###   ########.fr       */
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
	close_sem(philo->cutlery, SEM_CUTLERY);
	free(philo);
}

void	close_t_over(t_over *supervise)
{
	close_sem(supervise->sem_fed, SEM_FED);
	close_sem(supervise->sem_death, SEM_DEATH);
}

bool	get_sem_names(t_philo *philo, int nb)
{
	int		i;

	i = 0;
	philo->supervise.fed_sem_names = ft_calloc(nb + 1, sizeof(char *));
	if (!philo->supervise.fed_sem_names)
		return (NULL);
	philo->supervise.sem_fed = ft_calloc(nb + 1, sizeof(sem_t *));
	if (!philo->supervise.sem_fed)
		return (free(philo->supervise.fed_sem_names), false);
	while (i < nb)
	{
		philo->supervise.fed_sem_names[i] = ft_itoa(i);
		if (!philo->supervise.fed_sem_names[i])
			return (false);
		if (!init_sem(&philo->supervise->sem_fed[i], philo->supervise.fed_sem_names[i], 0))
			return (false);
		i++;
	}
	return (true);
}

bool	init_sem_fed(t_philo *philo, int nb)
{
	philo->supervise.fed_sem_names = get_sem_names(nb);
	if (!philo->supervise.fed_sem_names)
		return (false);
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
