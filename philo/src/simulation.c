/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:51:27 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/18 18:38:23 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (1) //verify if there is a dead condition (every step of the simulation)
	{
		//thinking
		print_action(philo, "is thinking");

		//try to eat

		//just to debug - INIT - 
		if (!philo->left_fork || !philo->right_fork)
		{
    		printf("Philosopher %d has invalid fork pointers.\n", philo->philo_id);
    		return NULL;
		}
		//just to debug - END - 

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

		//sleeping
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_sleep);
	}
	return (NULL);
}

void	*monitor_simulation(void *arg)
{
	unsigned int	i;
	t_table			*table;

	i = 0;
	table = (t_table *)arg;
	while (1)
	{
		i = 0; 
		while (i < table->num_philo)
		{
			if (get_current_time() - table->philos[i].time_meal \
			> table->time_die)
			{
				print_action(&table->philos[i], "died");
				table->end_meal_flg = 1;
				return (NULL);
			}
			i++;
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
