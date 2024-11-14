//header missing
static void    philo_routine(void *arg)
{
    t_philo *philo = (t_filo *)arg; 

    while (!table->end_meal_flag)
    {
        philo_eat(philo);
        philo_spleep_thing(philo);
        if (check_dead(philo)) //evaluate if this is the best solution against having a thread to control if some philo died
            break ; 
    }
    return (NULL); 
}

void	start_simulation(t_table *table)
{
    int i;
    struct timeval tv;

    i = 0; 
    gettimeofday(&tv, NULL);
    table->star_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    while(i < table->num_philo)
    {
        table->philos[i].time_meal = table->start_time;
        i++; 
    }
    //create a monitor thread
    if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]) != 0)
        error_exit("Failed to create monitor thread.\n");
    philo_routine(&table);
}
