/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:09:18 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/12 01:27:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	isnumber(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **argv)
{
	if (!argv[1] || !argv[2] || !argv[3] || !argv[4])
    	error_exit("Required arguments are missing.\n", NULL);
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| !isnumber(argv[1]))
		error_exit("Invalid philo number.\n", NULL);
	if (ft_atoi(argv[2]) <= 0 || !isnumber(argv[2]))
		error_exit("Invalid time to die.\n", NULL);
	if (ft_atoi(argv[3]) <= 0 || !isnumber(argv[3]))
		error_exit("Invalid time to eat.\n", NULL);
	if (ft_atoi(argv[4]) <= 0 || !isnumber(argv[4]))
		error_exit("Invalid time to sleep.\n", NULL);
	if (argv[5] && (!isnumber(argv[5]) || ft_atoi(argv[5]) <= 0)))
		error_exit("Invalid number of times each philosopher must eat.\n", NULL);
	return (0);
}