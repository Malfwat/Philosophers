/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:52:18 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/28 22:55:29 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ACTIONS_H
# define PHILO_ACTIONS_H

# include <stdbool.h>
# include <philo_structs.h>

void			drop_cutlery(t_philo *philo, enum e_fork *tab);
bool			get_cutlery(t_philo *philo, enum e_fork *tab);
bool			philo_sleep(t_philo *philo);
bool			eat(t_philo *philo);
bool			think(t_philo *philo);
void			get_action_tab(t_action *tab);
bool			set_death(t_table *table);
bool			is_death(t_table *table);
bool			is_dead(t_philo *philo);
bool			are_fed_up(t_table *table);
void			add_meal(t_philo *philo);
bool			waiting(t_philo *philo, t_time time_point, t_time to_wait);
void			my_print(t_philo *philo, char *str);

#endif /* PHILO_ACTIONS_H */