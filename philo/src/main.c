/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:22 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/16 01:01:01 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
        error_exit("Wrong number of arguments", table);
    check_args(argv);
	set_table(&table, argc, argv);
	summon_philos(&table);
	summon_forks(&table);
	fork_assignment(&table);
	start_simulation(&table);

//initialize the simulation loop:
    // 1. Eating: each philosopher locks two mutexes (forks) and simulates eating for time_to_eat milliseconds
    // 2. Sleeping: each philosopher "puts down" both forks (unlocks mutexes) and sleeps for time_to_sleep milliseconds
    // 3. Thinking: the philosopher transitions to thinking, ensuring they check their time_to_die threshold
    //track each philosopher last meal time. After each action, check if the philosopher's time without eating exceeds time_to_die. If so, log their death and terminate simulation

//Must have a function to keep the log and print alls the timestamps ans messages (Synchronize logging (e.g. mutex) to avoid log message overlap, ensuring a clear output
//clean up functions that destoy_mutexes and free_resources
    return (0); 
}