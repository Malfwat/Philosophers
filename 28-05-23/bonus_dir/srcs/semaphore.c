/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:50:25 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/02 17:05:44 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <philo_bonus_struct.h>
#include <philosopher_bonus.h>
#include <philo_bonus_defines.h>
#include <stdbool.h>
#include <unistd.h>

bool	init_sem(sem_t **sem, char *sem_name, int nb)
{
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 644, nb);
	if (*sem == SEM_FAILED)
		return (write(2, "sem_open failed\n", 16), false);
	return (true);
}

void	close_sem(sem_t *sem, char *sem_name)
{
	sem_close(sem);
	sem_unlink(sem_name);
}
