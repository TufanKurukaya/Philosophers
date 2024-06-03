/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   situation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  tkurukay < tkurukay@student.42kocaeli.com +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:14 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/03 13:12:23 by  tkurukay        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int	philo_dead(t_philo *philo)
{
	print_status(philo, "is dead\n");
	pthread_mutex_lock(&philo->data->print);
	philo->data->philo_dead = 1;
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

int	philo_join(t_data *data)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&data->mut);
		if (data->ready_count == data->philo_count)
		{
			pthread_mutex_lock(&data->time);
			data->start = get_time();
			pthread_mutex_unlock(&data->time);
			pthread_mutex_unlock(&data->die);
			pthread_mutex_unlock(&data->mut);
			break ;
		}
		pthread_mutex_unlock(&data->mut);
	}
	i = -1;
	while (++i < data->philo_count + 1)
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
	return (0);
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
	pthread_mutex_lock(&data->mut);
	data->ready_count++;
	pthread_mutex_unlock(&data->mut);
	pthread_mutex_lock(&data->die);
	pthread_mutex_unlock(&data->die);
	philo_life(philo, data);
	return (NULL);
}
