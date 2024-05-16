/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:45:32 by tkurukay          #+#    #+#             */
/*   Updated: 2024/05/16 13:45:24 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	check_forks(t_philo *philo);

void	waiting_area(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_table);
	usleep(100);
	pthread_mutex_unlock(&philo->data->m_table);
	check_forks(philo);
}

void	print_funk(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lld %d %s", get_time() - philo->last_eat, philo->id, str);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	eat(t_philo *philo)
{
	print_funk("is eating\n", philo);
	philo->last_eat = get_time();
	philo->eat_count = 0;
}

void	check_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->table[philo->fork[0]])
	{
		pthread_mutex_lock(&data->m_forks);
		philo->fork[0] = 0;
		if (data->table[philo->fork[1]])
		{
			pthread_mutex_lock(&data->m_forks);
			philo->fork[1] = 0;
			eat(philo);
			pthread_mutex_unlock(&data->m_forks);
		}
		else
		{
			pthread_mutex_unlock(&data->m_forks);
			waiting_area(philo);
		}
	}
	else
		waiting_area(philo);
}

void	*philo_funk(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	check_forks(philo);
	return (NULL);
}

int	create_philo(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->m_table, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->m_forks, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	while (++i < data->philo_count)
		if (pthread_create(&data->philo[i].thread, NULL, philo_funk,
				&data->philo[i]))
			return (1);
	while (1)
	{
		if (data->eat_count == 0)
			break ;
	}
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	return (0);
}
