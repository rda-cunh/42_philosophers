/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:35:16 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 17:43:14 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//thinking function
void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

//helper function to lock forks and avoid deadlocks (u25)
static void	lock_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}

//helper function to unlock forks and avoid deadlocks (u25)
static void	unlock_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

//eating function
void	philo_eat(t_philo *philo)
{
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		ft_usleep(philo->table->time_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	lock_forks(philo);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->time_meal = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_action(philo, "is eating");
	ft_usleep(philo->table->time_eat);
	unlock_forks(philo);
}

//sleeping function
void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->time_sleep);
}
