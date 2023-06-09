/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:56:14 by malfwa            #+#    #+#             */
/*   Updated: 2023/06/09 11:56:17 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

static unsigned int	find_len(unsigned int nbr)
{
	unsigned int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	fill_str(unsigned int len, int n, char *str, unsigned int *i)
{
	if (n == INT_MIN)
	{
		str[len -1] = '8';
		n = (n / 10) * -1;
	}
	if (n < 0)
		n *= -1;
	if (n > 9)
		fill_str(len, n / 10, str, i);
	str[*i] = (n % 10) + 48;
	(*i)++;
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;
	unsigned int	i;

	if (n < 0)
		len = find_len(-n) + 1;
	else
		len = find_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	i = 0;
	if (n < 0)
		str[i++] = '-';
	fill_str(len, n, str, &i);
	return (str);
}
