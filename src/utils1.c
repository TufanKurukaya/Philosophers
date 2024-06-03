/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  tkurukay < tkurukay@student.42kocaeli.com +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:28 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/03 16:11:08 by  tkurukay        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(250);
}

u_int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->m_check);
	if (philo->data->philo_dead)
	{
		pthread_mutex_unlock(&philo->data->m_check);
		return ;
	}
	pthread_mutex_lock(&philo->data->time);
	printf("%llu	%d	%s", (get_time() - philo->data->start), philo->id,
				status);
	pthread_mutex_unlock(&philo->data->time);
	pthread_mutex_unlock(&philo->data->m_check);
}
