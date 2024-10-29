/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:22 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/10/29 00:53:44 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
    int number_of_philosophers; //and number of forks
    int time_to_die; //time do die since last meal or beggining of simulation
    int time_to_eat; //time each philosopher needs to eat
    int time_to_sleep; //time each philosopher will spend sleeping
    int number_of_times_each_philosopher_must_eat; //simulation stops if all philosophers eat this number of times

    if (argc == 5 || argc == 6)
    {
        //read arguments and atoi them
        //store variables in a structure (t_info)

        //initialize philosophers as threads (usind a t_philo struct) [don't forget to assign them ids (i+1), forks and staarting times]
        //initialize mutexes to control the access to each fork and associate each philosoper with two adjacent threads
        
        //initialize the simulation loop:
            // 1. Eating: each philosopher locks two mutexes (forks) and simulates eating for time_to_eat milliseconds
            // 2. Sleeping: each philosopher "puts down" both forks (unlocks mutexes) and sleeps for time_to_sleep milliseconds
            // 3. Thinking: the philosopher transitions to thinking, ensuring they check their time_to_die threshold
        //track each philosopher last meal time. After each action, check if the philosopher's time without eating exceeds time_to_die. If so, log their death and terminate simulation

        //Must have a function to keep the log and print alls the timestamps ans messages (Synchronize logging (e.g. mutex) to avoid log message overlap, ensuring a clear output
        //clean um functions that destoy_mutexes and free_resources

    }
    return (0); 
}