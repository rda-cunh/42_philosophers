/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:22 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/18 02:26:29 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		error_exit("Wrong number of arguments", &table);
	check_args(argv);
	set_table(&table, argc, argv);
	summon_philos(&table);
	summon_forks(&table);
	fork_assignment(&table);
	start_simulation(&table);
	end_simulation(&table);
	return (0);
}
