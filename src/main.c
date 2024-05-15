/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:13:13 by tkurukay          #+#    #+#             */
/*   Updated: 2024/05/14 13:58:30 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <stdlib.h>

void	init_data(t_data *data)
{
	data->philo_count = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->eat_count = -1;
	data->start_time = 0;
	data->table = NULL;
	data->philo = NULL;
}


int	check_args_values(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av) <= 0)
			return (0);
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac < 2)
		return (0);
	if (ac < 5 || ac > 6)
		return (0);
	i = 0;
	while (av[++i])
		if (!check_args_values(av[i]))
			return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (1);
	init_data(&data);
	if (set_values(&data, av))
		return (ft_free("Error\n", &data), 1);

	if (create_philo(&data))
		return (ft_free("Error\n", &data), 1);
}
