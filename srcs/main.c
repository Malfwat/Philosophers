/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:12:16 by amouflet          #+#    #+#             */
/*   Updated: 2023/02/23 15:12:46 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int main(int ac, char **av)
{
	t_table			*table;
	pthread_mutex_t	mutex;
	if (is_good_params(ac, av) == false)
		return (printf("The params aren't ok!\n"),2);
	pthread_mutex_init(&mutex, NULL);
	table = create_table(av, &mutex);
	if (!table)
		return (pthread_mutex_destroy(&mutex), 2);
	first_launch(table);
	pthread_mutex_destroy(&mutex);
	free_table(table);
}
