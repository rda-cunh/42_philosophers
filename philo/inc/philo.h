/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:06 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 02:37:20 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//libraries
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//macros
# define PHILO_MAX 200

//structs
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	unsigned int	eat_count;
	long long		time_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	unsigned int	num_philo;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	unsigned int	num_meals_required;
	int				end_meal_flg;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
}	t_table;

//funtions
//initialization.c
void		start_simulation(t_table *table);
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

//utils.c
int			check_simulation_end(t_table *table);
void		print_action(t_philo *philo, const char *action);
int			ft_usleep(size_t milliseconds);
long long	get_current_time(void);
int			ft_atol(const char *str);

//exit.c

void		join_threads(t_table *table);
void		destroy_mutexes(t_table *table, int count);
void		clean_data(t_table *table);
void		end_simulation(t_table *table);
int			error_exit(char *msg, t_table *table);

#endif