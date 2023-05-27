/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:23:17 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/25 17:22:15 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <philo_structs.h>

bool			init_params(t_params *params, int ac, char **av);
void			*ft_calloc(size_t nmemb, size_t size);
t_table			*create_table(int ac, char **av);
t_supervisor	*create_supervisor(t_table *table);
void			simulation(t_supervisor *supervisor);
void			free_supervisor(t_supervisor *ptr);

void	my_print(t_philo *philo, char *str);
bool	philo_sleep(t_philo *philo);
bool	eat(t_philo *philo);
bool	think(t_philo *philo);
void	get_action_tab(t_action *tab);



bool	set_death(t_table *table);
bool	is_death(t_table *table);
bool	is_dead(t_philo *philo);
bool	are_fed_up(t_table *table);
void	add_meal(t_philo *philo);


void	ft_putstr(char *str);

bool	waiting(t_philo *philo, t_time time_point, t_time to_wait);

void	*death_routine(void *addr);


#endif /* PHILOSOPHERS_H */