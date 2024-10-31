/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:06 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/10/31 16:25:49 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //memory allocation
# include <string.h> //memset
# include <unistd.h> //write  and usleep
# include <sys/time.h> //gettimeoftheday
# include <pthread.h> //thread functions

//struct
typedef struct  s_philo
{
    //ID
    //Flags for eating, thinking or sleeping
    //is_alive flag (check if he died)
    //last_meal_time (timestamp in miliseconds) to record the time from the last time philo ate
    //left fort and right fort (pointers) to mutex forks the philo controls
    //eat_count to count the number of meals eated and control las program argument; 
}   t_philo; 

typedef struct  s_table
{
    // number_of_philosophers: the count of philosophers.
    // time_to_die: time limit before a philosopher starves if they don’t eat.
    // time_to_eat: duration of each eating session.
    // time_to_sleep: duration of each sleeping session.
    // meals_required (optional): the number of times each philosopher should eat, if it’s a stopping condition.
    // the forks (array of mutex w/ pthread_mutex_t)
    // start time timestamp (begginning of simulations)
    // an array of t_philo to track the philosophers
}   t_table;


//functions


#endif