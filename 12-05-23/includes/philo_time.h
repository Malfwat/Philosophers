/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 01:03:44 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/20 03:47:59 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <philo_defines.h>
# include <philo_struct.h>
# include <stdbool.h>

t_time	get_time_point(void);
t_time	get_timestamp_in_millisec(t_time start);
bool    synchronize_launch(t_philo *self);
t_time	get_departure_time(int table_len);
bool	wait_for_a_while(t_philo *self, t_case reason);

#endif /* PHILO_TIME_H */