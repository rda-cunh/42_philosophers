/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:19:55 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/16 00:58:37 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
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

//exit function in case of error
int	error_exit(char *msg, t_table *table)
{
	if (msg)
		printf("%s", msg);
	if (table->forks && table->philos)
	{
		destroy_mutexes(table);
		clean_data(table);
	}
	exit(1);
}
