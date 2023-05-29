/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:13:03 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/29 19:53:19 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(void)
{
	sem_t	*sem;

	sem_unlink("/empty_sem");
	sem = sem_open("/empty_sem", O_CREAT | O_EXCL, 644, 0);
	if (sem == SEM_FAILED)
		return (perror("sem_open"), 2);
	if (!fork())
	{
		sem_wait(sem);
		printf("sec\n");
		sem_close(sem);
		exit(0);
	}
	sleep(1);
	printf("first\n");
	sem_post(sem);
	wait(NULL);
	sem_close(sem);
	sem_unlink("/empty_sem");
	return (0);
}