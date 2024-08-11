/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:31:41 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/11 18:42:00 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INVALID_ARGS_ERR "Invalid arguments"
# define THREAD_CREATE_ERR "Failed to create a thread"
# define THREAD_JOIN_ERR "Failed to join a thread"
# define MALLOC_ERR "malloc() failed to allocate memory"
# define MUTEX_INIT_ERR "Failed to initialize mutex"
# define MAX_MIN_INT "Integer overflow"

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_philo
{
	char			*action;
	int				id;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	long			last_eat;
	long			start;
	pthread_mutex_t	last_eat_mutex;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_count;
	int				live_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				dead;
	int				philo_dead;
	pthread_mutex_t	print;
	pthread_mutex_t	philo_count_mtx;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

int					thread_handle(t_data *data);
long				ft_atol(const char *str);
long				get_time(void);
void				display_action(t_philo *philo, char *action);
int					check_args(char **av);
void				ft_usleep(long long time);

#endif