/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:15:28 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/24 19:43:53 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	if (data->philo_dead)

	return (NULL);
}

static void	one_philo(t_philo *philo)
{
	display(philo, FORK);
	ft_usleep(philo->data->die_time);
	display(philo, DEAD);
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
