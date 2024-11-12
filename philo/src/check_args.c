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
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| isnumber(argv[1]) == 1)
		exit_error("Invalid philo number\n");
	if (ft_atoi(argv[2]) <= 0 || isnumber(argv[2]) == 1)
		exit_error("Invalid time to die\n");
	if (ft_atoi(argv[3]) <= 0 || isnumber(argv[3]) == 1)
		exit_error ("Invalid time to eat\n");
	if (ft_atoi(argv[4]) <= 0 || isnumber(argv[4]) == 1)
		exit_error ("Invalid time to sleep\n");
	if (argv[5] && (ft_atoi(argv[5]) < 0 || isnumber(argv[5]) == 1))
		exit_error ("Invalid number of times each philosopher must eat\n");
	return (0);
}