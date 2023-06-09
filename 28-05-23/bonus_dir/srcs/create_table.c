/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:19:13 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/09 12:25:46 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus_struct.h>
#include <philosopher_bonus.h>
#include <philo_bonus_defines.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

void	close_sem_fed(t_over *supervise)
{
	int	i;

	i = 0;
	while (supervise->sem_fed && supervise->sem_fed[i])
	{
		close_sem(supervise->sem_fed[i], supervise->fed_sem_names[i]);
		i++;
	}
	free(supervise->sem_fed);
	supervise->sem_fed = NULL;
	free_tab((void **)supervise->fed_sem_names);
	supervise->fed_sem_names = NULL;
}

void	free_philo(t_philo *philo)
{
	if (!philo)
		return ;
	close_sem_fed(&philo->supervise);
	close_sem(philo->supervise.sem_death, SEM_DEATH);
	close_sem(philo->sem_print, SEM_PRINT);
	close_sem(philo->cutlery, SEM_CUTLERY);
	pthread_mutex_destroy(&philo->supervise.stop_mutx);
	free(philo);
}

bool	init_sem_fed(t_philo *philo, int nb)
{
	int		i;

	i = 0;
	philo->supervise.fed_sem_names = ft_calloc(nb + 1, sizeof(char *));
	if (!philo->supervise.fed_sem_names)
		return (false);
	philo->supervise.sem_fed = ft_calloc(nb + 1, sizeof(sem_t *));
	if (!philo->supervise.sem_fed)
		return (free(philo->supervise.fed_sem_names), false);
	while (i < nb)
	{
		philo->supervise.fed_sem_names[i] = ft_itoa(i);
		if (!philo->supervise.fed_sem_names[i])
			return (close_sem_fed(&philo->supervise), false);
		if (!init_sem(&philo->supervise.sem_fed[i], philo->supervise.fed_sem_names[i], 0))
			return (close_sem_fed(&philo->supervise), false);
		i++;
	}
	return (true);
}

bool	init_t_over(t_philo *philo, int nb_philo)
{
	if (!init_sem(&philo->supervise.sem_death, SEM_DEATH, 0))
		return (false);
	if (!init_sem_fed(philo, nb_philo))
		return (close_sem(philo->supervise.sem_death, SEM_DEATH), false);
	if (pthread_mutex_init(&philo->supervise.stop_mutx, NULL))
		return (free_philo(philo), false);
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
	if (!init_t_over(new, new->params.nb_philo))
		return (free(new), NULL);
	if (!init_sem(&new->cutlery, SEM_CUTLERY, new->params.nb_philo))
		return (free_philo(new), NULL);
	if (!init_sem(&new->sem_print, SEM_PRINT, 1))
		return (free_philo(new), NULL);
	return (new);
}
