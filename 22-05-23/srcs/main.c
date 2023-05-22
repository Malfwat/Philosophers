/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:22:37 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/22 20:54:38 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <stdio.h>
// #include <philo_struct.h>

int	main(int ac, char **av)
{
	t_supervisor	*supervisor;
	t_table	*table;
	

	table = create_table(ac, av);
	if (!table)
		return (2);
	supervisor = create_supervisor(table);
	if (!supervisor)
		return (2);
	simulation(supervisor);
	free_supervisor(supervisor);
	printf("done\n");
}