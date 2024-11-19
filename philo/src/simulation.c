/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:51:27 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/19 01:04:06 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (!philo->table->end_meal_flg)
	{
		//thinking
		print_action(philo, "is thinking");

		//try to eat
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");

		print_action(philo, "is eating");
		philo->time_meal = get_current_time();
		ft_usleep(philo->table->time_eat);
		philo->eat_count++;

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// If meals required are completed, break out of loop
		if (philo->table->num_meals_required > 0 && philo->eat_count >= philo->table->num_meals_required)
			break ;

		//sleeping
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_sleep);
	}
	return (NULL);
}

void	*monitor_simulation(void *arg)
{
	unsigned int	i;
	unsigned int	fat_philos;
	t_table			*table;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		fat_philos = 0; 
		while (i < table->num_philo)
		{
			//check if a philo died
			if (get_current_time() - table->philos[i].time_meal \
			> table->time_die)
			{
				print_action(&table->philos[i], "died");
				table->end_meal_flg = 1;
				return (NULL);
			}
			//check if a philo has eaten enough meals
			if (table->num_meals_required > 0 && \
			table->philos[i].eat_count >= table->num_meals_required)
			{
				fat_philos++;
			}
			i++;
		}
		//if all philos have eaten enough meals, end the simulation
		if (table->num_meals_required > 0 && fat_philos == table->num_philo)
		{
			table->end_meal_flg = 1;
			return (NULL);
		}
		ft_usleep(1000); //prevent busy waiting(check arguments for project defense!)
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
