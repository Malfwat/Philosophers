/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 01:03:44 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/22 20:21:38 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <philo_defines.h>
# include <philo_structs.h>
# include <stdbool.h>

t_time	get_time_point(void);
t_time	get_timestamp_in_millisec(t_time start);
bool    synchronize_launch(t_time time);
t_time	get_departure_time(int table_len);

#endif /* PHILO_TIME_H */