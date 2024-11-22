/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:19:55 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 17:48:05 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//funtion to join philo threads (end_simulation)
void	join_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			printf("Failed to join thread %u.\n", i + 1);
		i++;
	}
}

//function to clean all the mutexes
void	destroy_mutexes(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
}

//function to free forks and philos arrays
void	clean_data(t_table *table)
{
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

//join philo threads, destroy mutexes and free alocated memory
void	end_simulation(t_table *table)
{
	join_threads(table);
	destroy_mutexes(table, table->num_philo);
	clean_data(table);
}

//exit function in case of error
int	error_exit(char *msg, t_table *table)
{
	if (msg)
		printf("%s", msg);
	if (table)
	{
		if (table->forks && table->philos)
		{
			destroy_mutexes(table, table->num_philo);
			clean_data(table);
		}
	}
	exit(EXIT_FAILURE);
}
