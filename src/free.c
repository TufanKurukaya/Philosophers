/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  tkurukay < tkurukay@student.42kocaeli.com +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:51:54 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/03 16:11:08 by  tkurukay        ###   ########.fr       */
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
	free(data->forks);
	return (1);
}
