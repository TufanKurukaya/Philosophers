/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelemen <idelemen@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:17:00 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/04 15:25:32 by idelemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if ((ft_strlen(argv[i]) > 10) || (ft_atoi(argv[i]) <= 0))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;

	i = -1;
	nbr = 0;
	while (str[++i])
		if (ft_isdigit(str[i]))
			return (-1);
	i = 0;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i++] - '0');
		if (nbr > 2147483647)
			return (-1);
	}
	return (nbr);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
