/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:31:41 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/06 19:11:44 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	long			last_eat;
	char			*action;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				dead;
	int				eat_count;
	int				philo_dead;
	long			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philos;
}					t_data;

int					thread_handle(t_data *data);
long				ft_atol(const char *str);
long				get_time(void);
void				display_action(t_data *data, char *action);
int					check_args(char **av);
void				ft_usleep(long time);
#endif