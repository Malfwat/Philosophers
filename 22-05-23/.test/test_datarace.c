/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_datarace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:43:29 by amouflet          #+#    #+#             */
/*   Updated: 2023/05/24 17:15:37 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_pairs
{
	pthread_mutex_t	mutex;
	char			*value;
}t_pairs;

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s && s[i])
		i++;
	if (i)
		write(fd, s, i);
}

// void	*routine(void	*addr)
// {

// 	ft_putstr_fd((char *)addr, 1);
// 	return (NULL);
// }

// int	main(void)
// {
// 	char			*value;
// 	pthread_t		thread;
// 	pthread_mutex_t	mutex;

// 	value = "25";
// 	pthread_create(&thread, NULL, routine, value);
// 	ft_putstr_fd(value, 1);
// 	pthread_join(thread, NULL);
// 	return (0);
// }


void	*routine(void	*addr)
{
	t_pairs *ptr;

	ptr = (t_pairs *)addr;
	ft_putstr_fd(ptr->value, 1);
	// printf("routine %i\n", ptr->value);
	pthread_mutex_lock(&ptr->mutex);
	ptr->value = "21565";
	pthread_mutex_unlock(&ptr->mutex);
	return (NULL);
}

int	main(void)
{
	char			*value;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	value = "25";

	t_pairs	test = (t_pairs){mutex, value};
	pthread_mutex_init(&test.mutex, NULL);
	pthread_create(&thread, NULL, routine, &test);
	pthread_mutex_lock(&test.mutex);
	printf("main %s\n", test.value);
	pthread_mutex_unlock(&test.mutex);
	pthread_join(thread, NULL);
	printf("main %s\n", test.value);
	return (0);
}