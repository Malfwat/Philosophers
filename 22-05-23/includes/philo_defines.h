/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:55:45 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/25 18:01:32 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEFINES_H
# define PHILO_DEFINES_H

typedef long long t_time;
typedef int	t_stop;

# define INT_MAX_LEN 10
# define NB_MAX_PHILO 300
# define TIME_MIN 60
# define INFINITE -1
# define DEATH -1
# define LAUNCH_LAPS 350
# define FIRST 0
# define SEC 1

enum e_fork
{
	MY_FORK,
	RIGHT_FORK
};

#endif /* PHILO_DEFINES_H */