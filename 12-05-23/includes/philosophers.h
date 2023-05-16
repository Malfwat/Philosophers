/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:44 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/16 21:55:58 by amouflet         ###   ########.fr       */
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

void    prelaunch(t_table table);

// ft_atoi.c

int	ft_atoi(const char *nptr);

// utils.c 

bool	is_good_params(int ac, char **av);

// check_death

bool	have_to_quit(t_philo *self);
bool	is_dead(t_philo *self);
void	set_death(t_philo *self);

#endif /*PHILOSOPHERS_H*/
