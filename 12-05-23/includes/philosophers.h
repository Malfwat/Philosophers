/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:44 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/20 23:07:28 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <philo_struct.h>
# include <philo_defines.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
// simulation

void    prelaunch(t_table *table);

// ft_atoi.c

int	ft_atoi(const char *nptr);

// utils.c 

bool	is_good_params(int ac, char **av);

// check_death

bool	have_to_quit(t_pairs *self);
bool	is_dead(t_pairs *self);
void	set_death(t_pairs *self);

bool	add_pairs(t_table *table, t_philo *philo);

void	my_print(t_pairs *self, char *str);

#endif /*PHILOSOPHERS_H*/
