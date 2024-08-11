/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:16:28 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/11 13:51:39 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == 43 || str[i] == 45))
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		tmp = (tmp * 10) + (str[i++] - 48);
	if ((tmp * sign < -2147483648 || tmp * sign > 2147483647)
		&& printf("max int error\n"))
		return (1);
	return (tmp * sign);
}

long  get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	display_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->philo_dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	printf("%ld %d %s\n", get_time() - philo->start, philo->id + 1,
		action);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < 48 || av[i][j] > 57)
				return (printf("Error: Invalid argument\n"), 1);
	}
	return (0);
}
