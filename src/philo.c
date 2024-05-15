/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:45:32 by tkurukay          #+#    #+#             */
/*   Updated: 2024/05/15 12:29:48 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	waiting_area(t_philo *philo)
{

}

void	print_funk(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lld %d %s", get_time() - philo->last_eat, philo->id, str);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	eat(t_philo *philo)
{
}

void	check_forks(t_philo *philo)
{
	
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
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	return (0);
}
