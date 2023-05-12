/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:02:39 by amouflet          #+#    #+#             */
/*   Updated: 2023/02/01 15:53:56 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
