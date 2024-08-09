/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:15:28 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/06 19:27:28 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo, t_data *data);
static void	one_philo(t_data *data);

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	if (data->philo_count == 1)
	{
		one_philo(data);
	}
	while (data->philo_dead)
	{
		if (!data->philo_dead)
			break ;
		eat(philo, data);
	}
	return (NULL);
}

static void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	display_action(data, FORK);
	pthread_mutex_lock(&data->forks[philo->r_fork]);
	display_action(data, FORK);
	display_action(data, EATING);
	philo->last_eat = get_time();
	if (data->must_eat)
		philo->eat_count++;
	ft_usleep(data->eat_time);
	pthread_mutex_unlock(&data->forks[philo->l_fork]);
	pthread_mutex_unlock(&data->forks[philo->r_fork]);
	display_action(data, SLEEPING);
	ft_usleep(data->sleep_time);
	display_action(data, THINKING);
}

static void	one_philo(t_data *data)
{
	display_action(data, FORK);
	ft_usleep(data->die_time);
	display_action(data, DEAD);
	return ;
}

int	thread_handle(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
			return (printf("Error: Thread creation failed\n"), 1);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (printf("Error: Thread join failed\n"), 1);
	}
	return (0);
}
