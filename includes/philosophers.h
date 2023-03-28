/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:44 by malfwa            #+#    #+#             */
/*   Updated: 2023/03/27 16:43:33 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <struct.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>

int                 ft_atoi(const char *nptr);
void                free_table(t_table *table);
t_table	            *create_table(char **av, pthread_mutex_t *mutex);
bool	            is_good_params(int ac, char **av);
unsigned long long  gettime(unsigned long long start); // millisecondes since epoch
unsigned long long  get_actual_time(void);
void	            drop_fork(t_philo *self);
bool	            is_fork(t_philo *self, unsigned long long time);
void				think(t_philo *self, unsigned long long time);
void                first_launch(t_table *table);

#endif /*PHILOSOPHERS_H*/
