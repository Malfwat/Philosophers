/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 23:31:51 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/16 19:36:07 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEFINES_H
# define PHILO_DEFINES_H

typedef unsigned long long t_time;

// time given to launch one thread correctely before the similation do start

# ifndef LAUNCH_LAPS
#  define LAUNCH_LAPS 150
# endif /* LAUNCH_LAPS */

typedef enum e_case
{
    EAT,
    SLEEP,
    THINK
}   t_case;

#endif /* PHILO_DEFINES_H */