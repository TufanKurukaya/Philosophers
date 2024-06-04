/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelemen <idelemen@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:07 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/04 16:50:15 by idelemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	die_control(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_check);
	pthread_mutex_lock(&philo->data->time);
	if (philo->data->philo_dead || (philo->data->must_eat != -1
			&& philo->eat_count == philo->data->must_eat))
	{
		pthread_mutex_unlock(&philo->data->time);
		pthread_mutex_unlock(&philo->data->m_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->time);
	pthread_mutex_unlock(&philo->data->m_check);
	return (0);
}

void	philo_life(t_philo *ph, t_data *data)
{
	if (!(ph->id % 2))
		ft_usleep(data->eat_time / 2);
	while ((data->must_eat != -1 && ph->eat_count == data->must_eat) != 1)
	{
		if (philo_take_forks(ph))
			break ;
		philo_eat(ph);
		philo_sleep(ph);
		if (die_control(ph))
			break ;
	}
}

void	*control_dead(void *arg)
{
	unsigned int	i;
	t_data			*data;

	data = arg;
	pthread_mutex_lock(&data->m_start);
	pthread_mutex_unlock(&data->m_start);
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (die_control(&data->philos[i]))
				break ;
			if (philo_check(&data->philos[i]))
				break ;
		}
		if (i != data->philo_count)
			break ;
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	unsigned int	i;
	pthread_t		thread;

	i = -1;
	pthread_mutex_lock(&data->m_start);
	if (pthread_create(&thread, NULL, control_dead, data))
		return (1);
	else
		while (++i < data->philo_count)
			if (pthread_create(&data->philos[i].thread, NULL, waiting_area,
					&data->philos[i]))
				return (1);
	if (philo_join(data))
		return (1);
	if (pthread_join(thread, NULL))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	if (check_args(argc, argv))
		return (ft_putstr_fd("Error: wrong argument\n", 2), 1);
	if (init_data(&data, argc, argv))
		return (ft_putstr_fd("Error: malloc error\n", 2), 1);
	if (start_simulation(&data))
		return (ft_putstr_fd("Error: thread error\n", 2), 1);
	free_data(&data);
	return (0);
}
