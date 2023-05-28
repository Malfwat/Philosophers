/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:22:37 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/28 22:08:04 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <stdio.h>

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
	return (0);
}