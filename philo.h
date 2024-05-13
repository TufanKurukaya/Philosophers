/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukay <tkurukay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:51 by tkurukay          #+#    #+#             */
/*   Updated: 2024/05/13 14:15:23 by tkurukay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long long		start_time;
	pthread_mutex_t	m_table;
	int				*table;
	pthread_t		*thread;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat;
	int				fork[2];
	struct s_data	*data;
}					t_philo;

int					create_table(t_data *data);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					set_values(t_data *data, char **av);
long long			get_time(void);
void				ft_free(char *str, t_data *data);
void				*ft_calloc(size_t count, size_t size);

#endif
