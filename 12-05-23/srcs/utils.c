/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:43:23 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/21 00:04:40 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <pthread.h>
#include <philo_defines.h>
#include <philo_time.h>
#include <philo_struct.h>

void	my_print(t_pairs *self, char *str)
{
	t_time	time;
	t_philo	*philo;

	time = get_timestamp_in_millisec(self->start);
	// printf("Je passe ici\n");
	// pthread_mutex_lock(&self->mutex_philo);
	philo = self->philo;
	pthread_mutex_lock(&self->print_mutex);
	// printf("Ici souci\n");
	printf("%-7.03lli %i %s\n", time, philo->index, str);
	pthread_mutex_unlock(&self->print_mutex);
	// pthread_mutex_unlock(&self->mutex_philo);
}

static bool	ft_is_digit(char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

bool	is_good_params(int ac, char **av)
{
	short	i;
	int		x;

	if (ac != 6 && ac != 5)
		return (false);
	i = 1;
	while (av[i])
	{
		x = 0;
		while (av[i][x])
		{
			if (ft_is_digit(av[i][x]) == false)
				return (false);
			x += 1;
		}
		i += 1;
	}
	return (true);
}
