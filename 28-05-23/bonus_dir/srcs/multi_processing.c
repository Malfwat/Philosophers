/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:38:46 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/12 18:28:42 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus_struct.h>
#include <philo_bonus_time.h>
#include <signal.h>
#include <philosopher_bonus.h>
#include <sys/wait.h>

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
	int		i;
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
