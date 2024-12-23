/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelemen <idelemen@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:11 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/07 12:44:57 by idelemen         ###   ########.fr       */
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
	philo_drop_forks(philo);
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
	int first_fork;
	int second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (first_fork > second_fork)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, "has taken a left fork\n");
	if (die_control(philo))
		return (pthread_mutex_unlock(&philo->data->forks[first_fork]), 1);
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (ft_usleep(philo->data->die_time), 1);
	}
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	if (die_control(philo))
		return (philo_drop_forks(philo), 1);
	print_status(philo, "has taken a right fork\n");
	return (0);
}

int	philo_drop_forks(t_philo *philo)
{
		int first_fork;
	int second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (first_fork > second_fork)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	return (0);
}
