/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cunh <rda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:59:41 by rda-cunh          #+#    #+#             */
/*   Updated: 2024/11/08 17:55:46 by rda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
    int result = 0;
    int sign = 1; 

    while (*str == ' ' || (*str >= 9 && *str <= 13))
    {
        str++;
    }
    if(*str == '-')
    {
        sign = -1;
        str++;
    }
    if(*str == '-' || *str == '+')
        str++;
    while(*str >= '0' && *str <= '9')
    {
        result = result * 10 + *str - '0';
        str++;
    }
    return (sign * result); 
}