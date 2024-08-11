/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:15:28 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/11 18:28:14 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo, t_data *data);
static void	philo_simulation(t_data *data, t_philo *philo);

static void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (philo->id % 2)
	{
		ft_usleep(data->eat_time);
		pthread_mutex_lock(&philo->last_eat_mutex);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->last_eat_mutex);
	}
	philo_simulation(data, philo);
	return (NULL);
}

static void	philo_simulation(t_data *data, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->philo_dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		if ((data->must_eat != -1 && philo->eat_count == data->must_eat))
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		if (!eat(philo, data))
		{
			if (data->must_eat && data->must_eat == philo->eat_count)
				break ;
			display_action(philo, SLEEPING);
			ft_usleep(data->sleep_time);
			display_action(philo, THINKING);
		}
	}
}

static int	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	display_action(philo, FORK);
	if (philo->l_fork == philo->r_fork)
	{
		ft_usleep(data->live_time);
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
		return (1);
	}
	pthread_mutex_lock(&data->forks[philo->r_fork]);
	display_action(philo, FORK);
	display_action(philo, EATING);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	if (data->must_eat != -1)
		philo->eat_count++;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	ft_usleep(data->eat_time);
	pthread_mutex_unlock(&data->forks[philo->r_fork]);
	pthread_mutex_unlock(&data->forks[philo->l_fork]);
	return (0);
}

void	stalker(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i >= data->philo_count)
			i = 0;
		pthread_mutex_lock(&data->philos[i].last_eat_mutex);
		if (data->must_eat != -1 && data->philos[i].eat_count == data->must_eat)
		{
			pthread_mutex_unlock(&data->philos[i].last_eat_mutex);
			break ;
		}
		if ((get_time() - data->philos[i].last_eat >= data->live_time))
		{
			display_action(&data->philos[i], DEAD);
			pthread_mutex_lock(&data->dead_mutex);
			data->philo_dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			pthread_mutex_unlock(&data->philos[i].last_eat_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->philos[i].last_eat_mutex);
		i++;
	}
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
	stalker(data);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (printf("Error: Thread join failed\n"), 1);
	}
	return (0);
}
