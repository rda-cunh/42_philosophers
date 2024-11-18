/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:19:55 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/18 02:24:36 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	destroy_mutexes(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

void	clean_data(t_table *table)
{
	free(table->forks);
	free(table->philos);
}

//join philo threads, destroy mutexes and free alocated memory
void	end_simulation(t_table *table)
{
	joint_threads(table);
	destroy_mutexes(table, table->num_philo);
	clean_data(table);
}

//exit function in case of error
int	error_exit(char *msg, t_table *table)
{
	if (msg)
		printf("%s", msg);
	if (table->forks && table->philos)
	{
		destroy_mutexes(table, table->num_philo);
		clean_data(table);
	}
	exit(1);
}


