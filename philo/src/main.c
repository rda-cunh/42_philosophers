/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:22 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/08 18:42:38 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	summon_philos(t_table *s_table)
{
	//initialize philosophers as threads (usind a t_philo struct) [don't forget to assign them ids (i+1), forks and staarting times]
}

void	set_table(t_table *table, int argc, char **argv)
{
    if (argc != 5 || argc != 6)
        error_exit("Wrong number of arguments");
    table->num_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argv == 6)
		table->meals_required = ft_atoi(argv[5]);
	else
		table->meals_required = -1;
	table->end_meal_flg = 0;
	if (table->num_philo < 1 || table->time_die < 1 || table->time_eat < 1 \
	|| table->time_sleep < 1 || (argc == 6 && table->meals_required < 1))
		error_exit("Invalid arguments"); 
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