/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelemen <idelemen@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:51:54 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/04 13:13:12 by idelemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

int	free_data(t_data *data)
{
	free_mutex(data);
	if (data->philos)
		free(data->philos);
	return (1);
}

int	free_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->m_check);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->m_start);
	pthread_mutex_destroy(&data->mtx);
	if (data->forks)
		free(data->forks);
	return (1);
}
