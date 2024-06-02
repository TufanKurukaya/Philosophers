/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:51:54 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/02 22:52:04 by tkurukay         ###   ########.fr       */
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
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->die);
	pthread_mutex_destroy(&data->mut);
	free(data->forks);
	return (1);
}
