/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:10:33 by amouflet          #+#    #+#             */
/*   Updated: 2023/06/12 18:29:05 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <philo_bonus_struct.h>
# include <philo_bonus_defines.h>
# include <stdbool.h>

char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);

t_philo	*create_philo(int ac, char **av);
void	free_philo(t_philo *philo);
void	close_sem(sem_t *sem, char *sem_name);
void	my_print(t_philo *philo, char *str);
bool	init_sem(sem_t **sem, char *sem_name, int nb);
bool	init_params(t_params *params, int ac, char **av);
void	launch_philo(t_philo *philo, pid_t *tab);
void	incremt_sem(sem_t *sem, int count_to_add);
void	wait_children(pid_t *array);
bool	is_dead(t_philo *philo);
bool	is_death(t_philo *philo);
void	free_tab(void **tab);
bool	get_cutlery(t_philo *philo);
void	drop_cutlery(sem_t *cutlery);
void	get_action_tab(t_action *tab);
void	incremt_sem(sem_t *sem, int count_to_add);
void	*are_fed_up(void *ptr);
void	*check_death_ending(void *ptr);
void	add_meal(t_philo *philo);
bool	set_death(t_philo *philo);
void	infanticide(pid_t *array);
void	wait_children(pid_t *array);

#endif /* PHILOSOPHER_BONUS_H */