/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:43 by amorel            #+#    #+#             */
/*   Updated: 2022/09/27 18:15:15 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	float	result;
	int		decim;
	int		sign;

	result = 0;
	decim = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str != '.' && *str)
	{
		result *= 10;
		result += (*str - '0');
		str++;
	}
	while (*str && *(++str))
	{
		decim++;
		result += (float)(*str - '0') / (float)ft_power(10, decim);
	}
	return (result * sign);
}
