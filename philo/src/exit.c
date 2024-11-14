/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:19:55 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/08 18:05:03 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//exit function in case of error
int	error_exit(char *error_msg)
{
	printf(error_msg);
	//must add structs and memory clean 
	return (1);  
}