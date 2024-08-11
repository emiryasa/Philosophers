/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:33:19 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/11 18:29:49 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	control_data(t_data *data)
{
	if (data->philo_count < 1 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->live_time < 60 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->eat_time < 60 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->sleep_time < 60 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->must_eat == 0)
		return (1);
	return (0);
}

void	destroy_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].last_eat_mutex);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_mutex);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].eat_count = 0;
		data->philos[i].action = NULL;
		data->philos[i].data = data;
		data->philos[i].last_eat = get_time();
		data->philos[i].start = get_time();
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->philo_count;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].last_eat_mutex, NULL);
	}
	pthread_mutex_init(&data->print, NULL);
}

void	init_data(t_data *data, int ac, char **av)
{
	data->philo_count = ft_atol(av[1]);
	data->live_time = ft_atol(av[2]);
	data->eat_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	if (ac == 6)
		data->must_eat = ft_atol(av[5]);
	else
		data->must_eat = -1;
	data->philo_dead = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->philo_count_mtx, NULL);
	init_philos(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	if (check_args(av))
		return (1);
	init_data(&data, ac, av);
	if (control_data(&data))
	{
		destroy_data(&data);
		free(data.forks);
		free(data.philos);
		return (1);
	}
	if (thread_handle(&data))
	{
		destroy_data(&data);
		free(data.forks);
		free(data.philos);
		return (1);
	}
	destroy_data(&data);
	free(data.forks);
	free(data.philos);
	return (0);
}
