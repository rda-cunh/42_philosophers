/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:06 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/21 02:30:33 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//libraries
# include <stdio.h> //printf
# include <stdlib.h> //memory allocation
# include <string.h> //memset
# include <unistd.h> //write and usleep
# include <sys/time.h> //gettimeoftheday
# include <pthread.h> //thread functions

//macros
# define PHILO_MAX 200

//structs
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t   	thread; //thread
	int         	philo_id; //philo ID 
	unsigned int	eat_count; //count the number of meals eated and control las program argument (when given)
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
	unsigned int	num_meals_required; //meals_required (optional): the number of times each philosopher should eat, if it’s a stopping condition.
	int				end_meal_flg; //flag that signals the end of the simulation (a philo died or meals required are achieved)
    long long		start_time; //start time timestamp (begginning of simulations)
	t_philo			*philos; //an array of t_philo to track the philosophers
	pthread_mutex_t *forks; //an array to the store the mutexes referenced in my philo struct
	pthread_mutex_t	print_mutex; //protects printing calls
	pthread_mutex_t	death_mutex; //protects end_meal_flag and the way death philo is checked
	pthread_mutex_t meal_mutex; //protects eat_count and meal time updates
}   t_table;

//funtions
//initialization.c
void		fork_assignment(t_table *table);
void		summon_forks(t_table *table);
void		summon_philos(t_table *table);
void		set_table(t_table *table, int argc, char **argv);

//check_args.c
int			isnumber(char *arg);
int			check_args(char **argv);

//simulation.c
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		*philo_routine(void *arg);
void		*monitor_simulation(void *arg);
void		start_simulation(t_table *table);

//utils.c
int			check_simulation_end(t_table *table);
void		print_action(t_philo *philo, const char *action);
int			ft_usleep(size_t milliseconds);
long long	get_current_time(void);
int			ft_atoi(const char *str);

//exit.c
void		join_threads(t_table *table);
void		destroy_mutexes(t_table *table, int count);
void		clean_data(t_table *table);
void		end_simulation(t_table *table);
int			error_exit(char *msg, t_table *table);

#endif