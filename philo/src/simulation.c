/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:51:27 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 13:45:28 by rda-cunh         ###   ########.fr       */
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

static int	check_philo_dead(t_philo *philo, t_table *table)
{
	long long		time_from_meal;

	pthread_mutex_lock(&table->meal_mutex);
	time_from_meal = get_current_time() - philo->time_meal;
	if (time_from_meal >= table->time_die)
	{
		print_action(philo, "died");
		pthread_mutex_lock(&table->death_mutex);
		table->end_meal_flg = 1;
		pthread_mutex_unlock(&table->death_mutex);
		pthread_mutex_unlock(&table->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->meal_mutex);
	return (0); 
}

static int	check_philos_are_full(t_table *table)
{
	unsigned int	i;
	unsigned int	fat_philos;

	i = 0;
	fat_philos = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_lock(&table->meal_mutex);
		if (table->num_meals_required > 0
			&& table->philos[i].eat_count >= table->num_meals_required)
			fat_philos++;
		pthread_mutex_unlock(&table->meal_mutex);
		i++;
	}
	if (fat_philos == table->num_philo)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->end_meal_flg = 1;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_simulation(void *arg)
{
	t_table			*table;
	unsigned int	i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (check_philo_dead(&table->philos[i], table))
				return (NULL);
			i++;
		}
		if (check_philos_are_full(table))
			return (NULL);
		ft_usleep(5);
	}
}

void	start_simulation(t_table *table)
{
	unsigned int	i;
	pthread_t		monitor_thread;

	i = 0;
	table->start_time = get_current_time();
	while (i < table->num_philo)
	{
		table->philos[i].time_meal = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine, \
		&table->philos[i]) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_join(table->philos[i].thread, NULL);
			}
			error_exit("Failed to create philosopher thread.\n", table);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_simulation, table) != 0)
		error_exit("Failed to create monitor thread.\n", table);
	pthread_join(monitor_thread, NULL);
}
