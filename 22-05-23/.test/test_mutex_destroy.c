/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mutex_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:45:26 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/22 16:48:24 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

int	main(void)
{
	pthread_mutex_t	mutex;

	if (pthread_mutex_destroy(&mutex))
		printf("errno\n");
	else
		printf("nop errno\n");
	return (0);
}