/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:50:56 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/16 18:50:00 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <struct.h>
#include <philosophers.h>
#include <table.h>
#include <stdio.h>

int main(int ac, char **av)
{
	t_table			*table;
	if (is_good_params(ac, av) == false)
		return (printf("The params aren't ok!\n"),2);
	table = create_table(av);
    prelaunch(table);
	free_table(table);
}
