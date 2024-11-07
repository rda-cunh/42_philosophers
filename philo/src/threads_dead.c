/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:35:12 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/07 16:03:29 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#define TIMES_TO_COUNT	21000
#define NC				"\e[0m"
#define YELLOW			"\e[33m"
#define BYELLOW			"\e[1;33m"
#define RED				"\e[31m"
#define GREEN			"\e[32m"

//create structure that contains the count and the mutex
typedef struct s_locks
{
	pthread_mutex_t lock1;
	pthread_mutex_t lock2;
	unsigned int 	count;
}	t_locks;
d
void	*thread_routine1(void *data)
{
	pthread_t		tid;
	t_counter		*counter; //this changed to a pointer to a stuct initialized in main
	unsigned int	i; 

	tid = pthread_self();
	counter = (t_counter *)data; 

	//lock the mutex and then prints the count at thread start
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Count at thread start = %u.%s\n", YELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	i = 0; 
	//loop to iterate the count	
	while (i < TIMES_TO_COUNT)
	{
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	//printing the count at thread end
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Final count = %u.%s\n", BYELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t		tid1;
	pthread_t		tid2;
	t_counter		counter; 

	//initialize the cont variable in the struct
	counter.count = 0;

	//initialize the mutex
	pthread_mutex_init(&counter.count_mutex, NULL);

	//print expected counting result
	printf("Main: Expected count is %s%u%s\n", GREEN, 2 * TIMES_TO_COUNT, NC); 

	//create two threads and print their ID
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("Main: Created second thread [%ld]\n", tid2);

	//thread joining and printing joining status
	pthread_join(tid1, NULL);
	printf("Main: Joining first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joining second thread [%ld]\n", tid2);
	
	//final count evaluation
	if (counter.count == 2 * TIMES_TO_COUNT)
		printf("%sMain: OK. Total count is %u.%s\n", GREEN, counter.count, NC);
	else
		printf("%sMain: ERROR! Total count is %u.%s\n", RED, counter.count, NC);	
	return (0);
}
