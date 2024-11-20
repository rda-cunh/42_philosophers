/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:51:27 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/20 03:04:37 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	// Special case for single philosopher
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		ft_usleep(philo->table->time_die); // Simulate waiting until death
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	// Normal case for multiple philosophers
	// Always lock forks in ascending order to prevent deadlock
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
	print_action(philo, "is eating");
	philo->time_meal = get_current_time();
	ft_usleep(philo->table->time_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->meal_mutex);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
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
	// Special case for single philosopher
	if (philo->table->num_philo == 1)
	{
		philo_think(philo);
		philo_eat(philo);
		return (NULL);
	}
	while (!philo->table->end_meal_flg)
	{
		philo_think(philo);

		if (philo->table->end_meal_flg)
			break ;

		philo_eat(philo);

		if (philo->table->end_meal_flg)
			break ;

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
	unsigned int	current_meals;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		fat_philos = 0;
		while (i < table->num_philo)
		{
			// Check if a philosopher has died
			pthread_mutex_lock(&table->meal_mutex);
			time_from_meal = get_current_time() - table->philos[i].time_meal;
			current_meals = table->philos[i].eat_count;
			pthread_mutex_unlock(&table->meal_mutex);

			if (time_from_meal >= table->time_die)
			{
				print_action(&table->philos[i], "died");
				pthread_mutex_lock(&table->death_mutex);
				table->end_meal_flg = 1;
				pthread_mutex_unlock(&table->death_mutex);
				return (NULL);
			}

			// Check if a philosopher has eaten enough meals
			if (table->num_meals_required > 0 && current_meals >= table->num_meals_required)
				fat_philos++;
			i++;
		}

		// End simulation if all philosophers are full
		if (table->num_meals_required > 0 && fat_philos == table->num_philo)
		{
			pthread_mutex_lock(&table->death_mutex);
			table->end_meal_flg = 1;
			pthread_mutex_unlock(&table->death_mutex);
			return (NULL);
		}
		ft_usleep(100); // Prevent busy waiting
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

	//evaluate to join philo threads here istead of in main (instead of end_simulation)
}
