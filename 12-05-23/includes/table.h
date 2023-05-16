/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:57:04 by malfwa            #+#    #+#             */
/*   Updated: 2023/05/14 01:06:05 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <philo_defines.h>

void	free_table(t_table *table);
t_philo	*new_philo(char **av, int index);
int		add_philo(t_table *table,char **av, int index);
t_table	*create_table(char **av);


#endif /* TABLE_H */