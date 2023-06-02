/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:54:58 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/02 14:12:55 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <philo_bonus_struct.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

void	simulation(t_philo *philo)
{
	printf("je suis %i\n", philo->index);
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
		kill(SIGKILL, array[i++]);
}

void	launch_philo(t_philo *philo, pid_t *tab)
{
	int	i;

	i = 0;
	while (i < philo->params.nb_philo)
	{
		tab[i] = fork();
		if (tab[i] == -1)
			return (infanticide(tab));
		if (!tab[i])
		{
			free(tab);
			philo->index = i;
			return (simulation(philo));
		}
		i++;
	}
}