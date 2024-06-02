/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:11 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/02 22:07:55 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_eat(t_philo *philo)
{
	print_status(philo, "is eating\n");
	ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->data->time);
	philo->eat_count++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->time);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping\n");
	ft_usleep(philo->data->sleep_time);
	print_status(philo, "is thinking\n");
	return (0);
}

int	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a left fork\n");
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (ft_usleep(philo->data->die_time), philo_dead(philo));
	}
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (die_control(philo))
	{
		philo_drop_forks(philo);
		return (1);
	}
	print_status(philo, "has taken a right fork\n");
	return (0);
}

int	philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	return (0);
}
