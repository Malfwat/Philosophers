/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:10:33 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/03 19:19:25 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <philo_bonus_struct.h>
# include <philo_bonus_defines.h>

void	*ft_calloc(size_t nmemb, size_t size);

t_philo	*create_philo(int ac, char **av);
void	free_philo(t_philo *philo);
void	close_sem(sem_t *sem, char *sem_name);
bool	init_sem(sem_t **sem, char *sem_name, int nb);
bool	init_params(t_params *params, int ac, char **av);
void	launch_philo(t_philo *philo, pid_t *tab);
void	incremt_sem(sem_t *sem, int count_to_add);
void	wait_children(pid_t *array);

#endif /* PHILOSOPHER_BONUS_H */