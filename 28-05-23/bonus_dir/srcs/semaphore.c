/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:50:25 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/31 17:01:30 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <philo_bonus_struct.h>
#include <philosopher_bonus.h>
#include <philo_bonus_defines.h>
#include <stdbool.h>

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

char	**get_sem_names(int nb_philo)
{
	char	**tab;

	tab = ft_calloc(nb_philo + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (i < nb_philo)
	{
		tab[i] = ft_itoa(i);
		if (!tab[i])
			return (free_tab(tab), NULL);
		i++;
	}
	return (tab);
}

bool	create_cutlery(sem_t **cutlery, int nb_philo)
{
	if (!nb_philo)
		return (false);
}
