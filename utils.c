/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:16:28 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/24 19:44:20 by eyasa            ###   ########.fr       */
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
		exit(1);
	return (tmp * sign);
}

long	ft_time(void)
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_display_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->philo_dead)
	{
		printf("%ld %d %s\n", ft_time() - philo->data->start, philo->id, action);
		if (action != DEAD)
			pthread_mutex_unlock(&philo->data->print);
	}
	else
		pthread_mutex_unlock(&philo->data->print);
}
