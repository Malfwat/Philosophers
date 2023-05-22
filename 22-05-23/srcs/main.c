/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:22:37 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/22 18:26:35 by amouflet         ###   ########.fr       */
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
	printf("done\n");
}