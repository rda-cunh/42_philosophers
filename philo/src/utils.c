/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:59:41 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/18 03:21:45 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_action(t_philo *philo, const char *action)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	long long				current_time;

	pthread_mutex_lock(&print_mutex);
	if (!philo->table->end_meal_flg)
	{
		current_time = get_current_time() - philo->table->start_time;
		printf("%lld %d %s\n", current_time, philo->philo_id, action);
	}
	pthread_mutex_unlock(&print_mutex);
}


//improved version of sleep function
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

//gets the current time in milliseconds
long long	get_current_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

//turn asci into intiger
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}
