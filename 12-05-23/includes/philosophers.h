/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:44 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/13 00:14:59 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <struct.h>

// manage_time.c

unsigned long long  get_timestamp_in_millisec(unsigned long long start);
unsigned long long  get_start(void);

// ft_atoi.c

int	ft_atoi(const char *nptr);

// utils.c 

bool	is_good_params(int ac, char **av);

#endif /*PHILOSOPHERS_H*/
