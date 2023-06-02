/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:44:20 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/02 14:09:51 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher_bonus.h>

int	main(int ac, char **av)
{
	t_philo	*philo;
	pid_t	*tab;

	philo = create_philo(ac, av);
	if (!philo)
		return (2);
	tab = ft_calloc(philo->params.nb_philo, sizeof(pid_t));
	if (!tab)
		return (free_philo(philo), 2);
	launch_philo(philo, tab);
	free_philo(philo);
	return (0);
}