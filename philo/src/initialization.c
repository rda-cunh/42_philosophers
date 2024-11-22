/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:50:39 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 02:46:27 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	fork_assignment(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->num_philo];
		i++;
	}
}

void	summon_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* table->num_philo);
	if (!table->forks)
		error_exit("Failed to allocate memory for forks.\n", table);
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_mutexes(table, i);
			free(table->forks);
			error_exit("Failed to initialize fork mutex.\n", NULL);
		}
		i++;
	}
}

void	summon_philos(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * (table->num_philo));
	if (!table->philos)
		error_exit("Failed to allocate memory for philosophers.\n", table);
	while (i < table->num_philo)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].table = table;
		i++;
	}
}

void	set_table(t_table *table, int argc, char **argv)
{
	table->num_philo = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]);
	table->time_eat = ft_atol(argv[3]);
	table->time_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_meals_required = ft_atol(argv[5]);
	else
		table->num_meals_required = -1;
	table->end_meal_flg = 0;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0 || \
		pthread_mutex_init(&table->death_mutex, NULL) != 0 || \
		pthread_mutex_init(&table->meal_mutex, NULL))
		error_exit("Failed to initialize mutexes", table);
}
