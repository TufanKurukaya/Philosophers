/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:01 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/07 11:57:50 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

int	init_philos(t_data *data)
{
	unsigned int	i;

	i = -1;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (1);
	while (++i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_count);
	if (!data->forks)
		return (1);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (error_init(data, i, 0));
		i++;
	}
	if (pthread_mutex_init(&data->m_check, NULL))
		return (error_init(data, i, 0));
	if (pthread_mutex_init(&data->time, NULL))
		return (error_init(data, i, 1));
	if (pthread_mutex_init(&data->mtx, NULL))
		return (error_init(data, i, 2));
	if (pthread_mutex_init(&data->m_start, NULL))
		return (error_init(data, i, 3));
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->must_eat = -1;
	data->ready_count = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->philo_dead = 0;
	data->start = 0;
	data->philos = NULL;
	data->forks = NULL;
	if (init_mutex(data))
		return (1);
	if (init_philos(data))
		return (free_data(data), 1);
	return (0);
}
