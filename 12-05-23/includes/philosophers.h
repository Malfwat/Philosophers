/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:44 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/16 18:50:22 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <struct.h>
# include <philo_defines.h>

// simulation

void    prelaunch(t_table table)

// ft_atoi.c

int	ft_atoi(const char *nptr);

// utils.c 

bool	is_good_params(int ac, char **av);

#endif /*PHILOSOPHERS_H*/
