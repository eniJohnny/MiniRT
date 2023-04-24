/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:43 by amorel            #+#    #+#             */
/*   Updated: 2022/10/21 18:47:37 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *str)
{
	double	result;
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
	while (*str != '.' && *str != '\n' && *str)
	{
		result *= 10;
		result += (*str - '0');
		str++;
	}
	while (*str && *str != '\n' && *(++str))
	{
		decim++;
		result += (double)(*str - '0') / (double)ft_power(10, decim);
	}
	return (result * sign);
}
