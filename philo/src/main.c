/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:22 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/12 02:00:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	summon_forks(t_table *table)
{
	int i;

	i = 0;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_philo)
	if (!table->forks)
		error_exit("Failed to allocate memory for forks.");
	while(i < table->num_philo)
	{
		
	}
}


void	summon_philos(t_table *table)
{
	int i;

	i = 0; 
	table->philos = (t_philo *)malloc(sizeof(t_philo) * (table->num_philo));
	if (!table->philos)
		exit_error("Failed to allocate memory for philosophers.\n");
	while(i < table->num_philo)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].flg_is_alive = 1; 
		table->philos[i].eat_count = 0;
		table->philos[i].time_meal = table->start_time;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->num_philo];
		table->philos[i].table = table; 
		if(pthtead_create(&table->philos[i].thread, NULL, philo_routine, &table_philos[i]) != 0)
			error_exit("Failed to create thread.\n")
		i++; 
	}
}

void	set_table(t_table *table, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        error_exit("Wrong number of arguments");
	else
		check_args(argv); 
    table->num_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_meals_required = ft_atoi(argv[5]);
	else
		table->num_meals_required = -1;
	table->end_meal_flg = 0;
}

int main(int argc, char **argv)
{
    t_table	table; 

	set_table(&table, argc, argv);
	summon_philos(&table);

//initialize mutexes to control the access to each fork and associate each philosoper with two adjacent threads
        
//initialize the simulation loop:
    // 1. Eating: each philosopher locks two mutexes (forks) and simulates eating for time_to_eat milliseconds
    // 2. Sleeping: each philosopher "puts down" both forks (unlocks mutexes) and sleeps for time_to_sleep milliseconds
    // 3. Thinking: the philosopher transitions to thinking, ensuring they check their time_to_die threshold
    //track each philosopher last meal time. After each action, check if the philosopher's time without eating exceeds time_to_die. If so, log their death and terminate simulation

//Must have a function to keep the log and print alls the timestamps ans messages (Synchronize logging (e.g. mutex) to avoid log message overlap, ensuring a clear output
//clean um functions that destoy_mutexes and free_resources

    return (0); 
}