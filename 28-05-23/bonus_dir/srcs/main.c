/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:44:20 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/02 13:35:35 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher_bonus.h>

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = create_philo(ac, av);
	if (!philo)
		return (2);
	sem_wait(philo->cutlery);
	free_philo(philo);
	return (0);
}