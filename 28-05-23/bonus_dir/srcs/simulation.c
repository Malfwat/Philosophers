/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:54:58 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/12 18:29:22 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <philo_bonus_struct.h>
#include <philo_bonus_time.h>
#include <philosopher_bonus.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

bool	launch_thread(t_philo *philo)
{
	if (pthread_create(&philo->supervise.check_death, \
		NULL, check_death_ending, philo))
		return (false);
	if (pthread_create(&philo->supervise.check_fed, \
		NULL, are_fed_up, philo))
		return (false);
	return (true);
}

void	spread_launch(t_philo *philo)
{
	int	nb_p;

	nb_p = philo->params.nb_philo;
	if (philo->index % 2)
		my_print(philo, "is thinking");
	if (nb_p % 2 && philo->index == nb_p)
		waiting(philo, philo->start, philo->params.eating \
		+ philo->params.eating / 2);
	else if (philo->index % 2)
		waiting(philo, philo->start, philo->params.eating);
}

void	simulation(t_philo *philo)
{
	t_action	action[4];
	int			i;

	i = 0;
	get_action_tab(action);
	synchronize_launch(philo->start);
	if (!launch_thread(philo))
		return (free_philo(philo), exit(0));
	spread_launch(philo);
	while (!is_dead(philo) && !is_death(philo))
	{
		if (!action[i])
			i = 0;
		if (!action[i++](philo))
			break ;
	}
	incremt_sem(philo->supervise.sem_death, 1);
	incremt_sem(philo->supervise.sem_fed[philo->index - 1], \
	philo->params.nb_philo);
	pthread_join(philo->supervise.check_death, NULL);
	pthread_join(philo->supervise.check_fed, NULL);
	return (free_philo(philo), exit(0));
}

void	launch_philo(t_philo *philo, pid_t *tab)
{
	int	i;

	i = 0;
	philo->start = get_departure_time(philo->params.nb_philo);
	philo->last_meal = philo->start;
	while (i < philo->params.nb_philo)
	{
		tab[i] = fork();
		if (tab[i] == -1)
			return (infanticide(tab));
		if (!tab[i])
		{
			free(tab);
			philo->index = i + 1;
			return (simulation(philo));
		}
		i++;
	}
}
