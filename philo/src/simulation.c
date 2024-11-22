/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:51:27 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 02:48:46 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

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
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->time_meal = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_action(philo, "is eating");
	ft_usleep(philo->table->time_eat);
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

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->time_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philo == 1)
	{
		philo_think(philo);
		philo_eat(philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		if (philo->table->end_meal_flg)
		{
			pthread_mutex_unlock(&philo->table->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_mutex);
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	*monitor_simulation(void *arg)
{
	t_table			*table;
	unsigned int	i;
	unsigned int	fat_philos;
	long long		time_from_meal;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		fat_philos = 0;
		while (i < table->num_philo)
		{
			pthread_mutex_lock(&table->meal_mutex);
			time_from_meal = get_current_time() - table->philos[i].time_meal;
			if (time_from_meal >= table->time_die)
			{
				print_action(&table->philos[i], "died");
				pthread_mutex_lock(&table->death_mutex);
				table->end_meal_flg = 1;
				pthread_mutex_unlock(&table->death_mutex);
				pthread_mutex_unlock(&table->meal_mutex);
				return (NULL);
			}
			if (table->num_meals_required > 0 \
			&& table->philos[i].eat_count >= table->num_meals_required)
				fat_philos++;
			pthread_mutex_unlock(&table->meal_mutex);
			i++;
		}
		if (table->num_meals_required > 0 && fat_philos == table->num_philo)
		{
			pthread_mutex_lock(&table->death_mutex);
			table->end_meal_flg = 1;
			pthread_mutex_unlock(&table->death_mutex);
			return (NULL);
		}
		ft_usleep(5);
	}
}
