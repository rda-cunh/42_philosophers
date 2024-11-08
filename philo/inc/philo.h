/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:06 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/08 18:36:07 by rda-cunh         ###   ########.fr       */
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

//structs (must check during implementation!)
typedef struct  s_philo
{
	pthread_t   	thread; //thread
	int         	philo_id; //philo ID 
	int 			flg_is_alive; //flag to sinalize of philo died (not shure if needed!)
	int				eat_count; //count the number of meals eated and control las program argument (when given)
	long long		time_meal; //time from last meal (to check if he died)
	pthread_mutex_t	*right_fork;  //right fork (pointer) to mutex the philo controls
	pthread_mutex_t *left_fork; //left fork (pointer) to mutex the philo controls
	t_table			*table; //pointer to access table struct
}   t_philo; 

typedef struct  s_table
{
	unsigned int	num_philo; //number_of_philosophers: the count of philosophers
	long long		time_die; //time_to_die: time limit before a philosopher starves if they don’t eat.
	long long		time_eat; //time_to_eat: duration of each eating session
	long long		time_sleep; //time_to_sleep: duration of each sleeping session
	unsigned int	meals_required; //meals_required (optional): the number of times each philosopher should eat, if it’s a stopping condition.
	int				end_meal_flg; //flag that signals the end of the simulation (a philo died or meals required are achieved)
    long long		start_time; //start time timestamp (begginning of simulations)
	t_philo			*philos; //an array of t_philo to track the philosophers
	pthread_mutex_t *forks; //an array to the store the mutexes referenced in my philo struct
}   t_table;


//funtions
//main.c
void	set_table(t_table *table, int argc, char **argv);
void	summon_philos(t_table s_table); 

//utils.c
int		ft_atoi(const char *str); 

//exit.c
int		error_exit(char *error_msg); 


#endif