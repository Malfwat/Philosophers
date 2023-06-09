/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_time.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:28:49 by malfwa            #+#    #+#             */
/*   Updated: 2023/06/09 12:30:56 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_TIME_H
# define PHILO_BONUS_TIME_H

# include <philo_bonus_defines.h>
# include <philo_bonus_struct.h>
# include <stdbool.h>

t_time	get_time_point(void);
t_time	get_timestamp_in_millisec(t_time start);
void	synchronize_launch(t_time time);
t_time	get_departure_time(int table_len);
bool	waiting(t_philo *philo, t_time time_point, t_time to_wait);

#endif /* PHILO_BONUS_TIME_H */