/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:51:54 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/06 18:12:30 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

int	free_data(t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (free_mutex(data))
		exit_code = 1;
	if (data->philos)
		free(data->philos);
	return (exit_code);
}

int	free_mutex(t_data *data)
{
	unsigned int	i;
	int				exit_code;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			exit_code = 1;
		i++;
	}
	if (pthread_mutex_destroy(&data->m_check))
		exit_code = 1;
	if (pthread_mutex_destroy(&data->time))
		exit_code = 1;
	if (pthread_mutex_destroy(&data->m_start))
		exit_code = 1;
	if (pthread_mutex_destroy(&data->mtx))
		exit_code = 1;
	if (data->forks)
		free(data->forks);
	return (exit_code);
}
int	error_init(t_data *data, int len, int m_num)
{
	if (m_num == 1)
		pthread_mutex_destroy(&data->m_start);
	else if (m_num <= 2)
		pthread_mutex_destroy(&data->time);
	else if (m_num <= 3)
		pthread_mutex_destroy(&data->m_check);
	else if (m_num <= 4)
		pthread_mutex_destroy(&data->forks[len]);
	while (--len >= 0)
		pthread_mutex_destroy(&data->forks[len]);
	return (1);
}

int	error_create(t_data *data, int len)
{
	int	exit_code;

	exit_code = 0;
	pthread_mutex_unlock(&data->m_start);
	while (--len >= 0)
		pthread_join(data->philos[len].thread, NULL);
	return (free_data(data));
}
