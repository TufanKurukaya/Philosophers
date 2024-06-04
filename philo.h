/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelemen <idelemen@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:05:54 by tkurukay          #+#    #+#             */
/*   Updated: 2024/06/04 13:14:26 by idelemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	u_int64_t		last_eat;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				ready_count;
	unsigned int	philo_count;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				must_eat;
	int				philo_dead;
	u_int64_t		start;
	pthread_mutex_t	mtx;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_check;
	pthread_mutex_t	m_start;
	pthread_mutex_t	time;
	t_philo			*philos;
}					t_data;

// free.c
int					free_data(t_data *data);
int					free_mutex(t_data *data);
// init.c
int					init_philos(t_data *data);
int					init_mutex(t_data *data);
int					init_data(t_data *data, int argc, char **argv);
// main.c
int					die_control(t_philo *philo);
void				philo_life(t_philo *philo, t_data *data);
void				*control_dead(void *data);
int					start_simulation(t_data *data);
// simulation.c
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					philo_take_forks(t_philo *philo);
int					philo_drop_forks(t_philo *philo);
// situation.c
int					philo_dead(t_philo *philo);
int					philo_join(t_data *data);
int					philo_check(t_philo *philo);
void				*waiting_area(void *arg);
// utils.c
int					check_args(int argc, char **argv);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strlen(const char *s);
// utils1.c
void				ft_usleep(u_int64_t time);
u_int64_t			get_time(void);
void				ft_putstr_fd(char *s, int fd);
void				print_status(t_philo *philo, char *status);

#endif
