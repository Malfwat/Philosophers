/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:26:29 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/22 17:59:45 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_structs.h>
#include <philo_defines.h>
#include <stdbool.h>
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	value;
	int	i;

	i = 0;
	value = 0;
	sign = 1;
	while (nptr && ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == 32))
		i++;
	if (nptr && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr && (nptr[i] <= '9' && nptr[i] >= '0'))
	{
		value = value * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * value);
}

int	print_usage(void)
{
	printf("Usage:\n\t./philo number_of_philosophers time_to_die "\
	"time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (2);
}

bool	is_positiv_int(char	*number)
{
	int	i;

	if (!number)
		return (false);
	i = 0;
	while (number[i] <= '9' && number[i] >= '0')
		i++;
	if (number[i] || i > INT_MAX_LEN)
		return (false);
	return (true);
}

bool	check_params(char **av)
{
	int	i;
	
	i = 1;
	while (av[i])
	{
		if (!is_positiv_int(av[i++]))
		{
			printf("Only positiv INT\n");
			return (print_usage(), false);
		}
	}
	return (true);
}

bool	init_params(t_params *params, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (print_usage());
	if (!check_params(av))
		return (false);
	params->nb_of_philo = ft_atoi(av[1]);
	if (params->nb_of_philo > NB_MAX_PHILO || !params->nb_of_philo)
	{
		printf("The number of philosophers must be between 0 and 300");
		return (print_usage(), false);
	}
	params->dying = ft_atoi(av[2]);
	params->eating = ft_atoi(av[3]);
	params->sleeping = ft_atoi(av[4]);
	if (params->sleeping < TIME_MIN || params->eating < TIME_MIN)
	{
		printf("The time laps must be equal or greater than 60");
		return (print_usage(), false);
	}
	params->nb_of_meal_needed = (int []){ft_atoi(av[5]) , INFINITE}[(av[5] == NULL)];
	return (true);
}