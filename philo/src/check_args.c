/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:09:18 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/22 02:15:41 by rda-cunh         ###   ########.fr       */
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
	if (ft_atol(argv[1]) > PHILO_MAX || ft_atol(argv[1]) <= 0
		|| !isnumber(argv[1]))
		error_exit("Invalid philo number.\n", NULL);
	if (ft_atol(argv[2]) <= 0 || !isnumber(argv[2]))
		error_exit("Invalid time to die.\n", NULL);
	if (ft_atol(argv[3]) <= 0 || !isnumber(argv[3]))
		error_exit("Invalid time to eat.\n", NULL);
	if (ft_atol(argv[4]) <= 0 || !isnumber(argv[4]))
		error_exit("Invalid time to sleep.\n", NULL);
	if (argv[5] && (!isnumber(argv[5]) || ft_atol(argv[5]) <= 0))
		error_exit("Invalid number of times each philo must eat.\n", NULL);
	return (0);
}
