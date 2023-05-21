/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 23:31:51 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/21 22:41:29 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEFINES_H
# define PHILO_DEFINES_H

typedef long long t_time;

// time given to launch one thread correctely before the similation do start

# ifndef LAUNCH_LAPS
#  define LAUNCH_LAPS 150
# endif /* LAUNCH_LAPS */

# define INFINITE -1

typedef enum e_case
{
    EAT,
    SLEEP,
    THINK,
    DIE
}   t_case;

#endif /* PHILO_DEFINES_H */