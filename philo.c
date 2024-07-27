/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:33:19 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/27 13:21:42 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print, NULL);
}

void	ft_init(t_data *data, int ac, char **av)
{
	int	i;

	data->philo_count = ft_atol(av[1]);
	data->die_time = ft_atol(av[2]);
	data->eat_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	data->must_eat = (ac == 6) ? ft_atol(av[5]) : -1;
	data->dead = 0;
	data->eat_count = 0;
	data->philo_dead = 1;
	data->start = ft_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = data->start;
		data->philos[i].action = NULL;
		data->philos[i].data = data;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->philo_count;
	}
	init_mutex(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	ft_init(&data, ac, av);
	if (thread_handle(&data))
		return (1);
	return (0);
}
