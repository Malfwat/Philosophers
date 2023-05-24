/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:18:17 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/24 16:14:05 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <philo_time.h>
#include <stdio.h>
#include <philo_structs.h>
#include <philo_defines.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	max_int;
	char	*tmp;
	size_t	i;
	size_t	value_asked;

	max_int = INT_MAX;
	i = 0;
	if (nmemb == 0 || size == 0)
	{
		tmp = malloc(sizeof(char));
		if (tmp)
			tmp[0] = 0;
		return ((void *)tmp);
	}
	if (nmemb > max_int / size || size > max_int / nmemb)
		return (NULL);
	value_asked = nmemb * size;
	tmp = malloc((value_asked));
	if (tmp == NULL)
		return (NULL);
	while (i < value_asked)
		tmp[i++] = 0;
	return ((void *)tmp);
}

void	my_print(t_philo *philo, char *str)
{
	t_time	time;
	
	pthread_mutex_lock(philo->table->mutex_print);
	time = get_timestamp_in_millisec(philo->table->start);
	if (!philo->table->stop)
		printf("%-7.03lli %i %s\n", time, philo->index, str);
	pthread_mutex_unlock(philo->table->mutex_print);
}