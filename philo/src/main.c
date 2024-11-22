/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:22 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 19:18:55 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//assign left and right forks to each philosopher
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

//allocate memory and create the forks (mutexes)
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

//initializes the philo struct
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

//initializes the table (main program struct)
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
		error_exit("Failed to initialize mutexes.\n", table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		error_exit("Wrong number of arguments.\n", NULL);
	check_args(argv);
	set_table(&table, argc, argv);
	summon_philos(&table);
	summon_forks(&table);
	fork_assignment(&table);
	start_simulation(&table);
	end_simulation(&table);
	return (0);
}
