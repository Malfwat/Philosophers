/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pthread_detach.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:29:28 by malfwa            #+#    #+#             */
/*   Updated: 2023/03/29 01:19:18 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	*func(void *tmp)
{
	printf("J'arrive ds le premier thread\n");
	pthread_mutex_lock((pthread_mutex_t *)tmp);

	printf("Je suis passe\n");

	pthread_mutex_unlock((pthread_mutex_t *)tmp);
	return (NULL);
}

void	*supervisor(void *tmp)
{
	// pthread_t		test;

	// (void)tmp;
	printf("J'arrive ds le superviseur\n");
	// test = *(pthread_t *)tmp;
	sleep(2);
	pthread_mutex_unlock(tmp);
	return (NULL);
}

int main(void)
{
	pthread_t		test;
	pthread_t		supervise;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	pthread_create(&test, NULL, func, &mutex);
	pthread_create(&supervise, NULL, supervisor, &mutex);
	pthread_join(supervise, NULL);
	pthread_join(test, NULL);
	printf("valeur de sortie unlock %i \n", pthread_mutex_unlock(&mutex));
	pthread_mutex_destroy(&mutex);
	return (0);
}