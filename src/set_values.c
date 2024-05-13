/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:13:22 by tkurukay          #+#    #+#             */
/*   Updated: 2024/05/13 14:36:08 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <stdlib.h>

void	*philo_funk(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->m_table);
	return (NULL);
}

void	check_forks(t_data *data)
{
}

int	create_table(t_data *data)
{
	int	i;

	i = -1;
	data->table = ft_calloc(sizeof(int), data->philo_count);
	if (!data->table)
		return (1);
	while (++i < data->philo_count)
		data->table[i] = 1;
	return (0);
}

void	set_philo_value(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].last_eat = data->start_time;
		data->philo[i].data = data;
		data->philo[i].fork[0] = i;
		data->philo[i].fork[1] = (i + 1) % data->philo_count;
		data->philo[i].data = data;
	}
}
int	set_values(t_data *data, char **av)
{
	int	i;

	i = -1;
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->eat_count = -1;
	if (av[5])
		data->eat_count = ft_atoi(av[5]);
	data->start_time = get_time();
	data->philo = ft_calloc(sizeof(t_philo), data->philo_count);
	if (!data->philo)
		return (1);
	data->philo = ft_calloc(sizeof(pthread_t), data->philo_count);
	if (!data->thread)
		return (1);
	set_philo_value(data);
	if (create_table(data))
		return (1);
	return (0);
}
