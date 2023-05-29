/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:23:17 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/28 22:58:09 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <philo_structs.h>
# include <unistd.h>

bool			init_params(t_params *params, int ac, char **av);
void			*ft_calloc(size_t nmemb, size_t size);
t_table			*create_table(int ac, char **av);
t_supervisor	*create_supervisor(t_table *table);
void			simulation(t_supervisor *supervisor);
void			free_supervisor(t_supervisor *ptr);

#endif /* PHILOSOPHERS_H */