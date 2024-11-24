/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   situation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:14 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/07 12:06:59 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_check);
	philo->data->philo_dead = 1;
	pthread_mutex_unlock(&philo->data->m_check);
	printf("%lu	%d	is died\n", get_time() - philo->data->start, philo->id);
	return (1);
}

int	philo_join(t_data *data)
{
	unsigned int	i;
	int				exit_code;

	exit_code = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mtx);
		if (data->ready_count == data->philo_count)
		{
			pthread_mutex_lock(&data->time);
			data->start = get_time();
			pthread_mutex_unlock(&data->time);
			pthread_mutex_unlock(&data->m_start);
			pthread_mutex_unlock(&data->mtx);
			break ;
		}
		pthread_mutex_unlock(&data->mtx);
	}
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(data->philos[i].thread, NULL))
			exit_code = 1;
	return (exit_code);
}

int	philo_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->time);
	if (philo->last_eat == 0)
		philo->last_eat = philo->data->start;
	if (philo->data->die_time <= get_time() - philo->last_eat)
		return (pthread_mutex_unlock(&philo->data->time), philo_dead(philo));
	pthread_mutex_unlock(&philo->data->time);
	return (0);
}

void	*waiting_area(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&data->mtx);
	data->ready_count++;
	pthread_mutex_unlock(&data->mtx);
	pthread_mutex_lock(&data->m_start);
	pthread_mutex_unlock(&data->m_start);
	philo_life(philo, data);
	return (NULL);
}
