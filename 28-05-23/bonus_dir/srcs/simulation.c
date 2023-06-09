/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:54:58 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/09 21:26:56 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <philo_bonus_struct.h>
#include <philo_bonus_time.h>
#include <philosopher_bonus.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

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
	philo->last_meal = philo->start;
	get_action_tab(action);
	synchronize_launch(philo->start);
	spread_launch(philo);
	// my_print(philo, "");
	is_dead(philo);
	while (/* !is_death(philo) */ action[i])
	{
		if (!action[i])
			i = 0;
		is_dead(philo);
		if (!action[i](philo))
			break ;
		is_dead(philo);
		i++;
	}
	free_philo(philo);
	exit(0);
}

void	infanticide(pid_t *array)
{
	int	i;

	i = 0;
	while (array[i] && array[i] != -1)
		kill(SIGKILL, array[i++]);
}

void	wait_children(pid_t *array)
{
	int	i;

	i = 0;
	while (array[i] && array[i] != -1)
		waitpid(array[i++], NULL, 0);
}

void	launch_philo(t_philo *philo, pid_t *tab)
{
	int	i;

	i = 0;
	philo->start = get_departure_time(philo->params.nb_philo);
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