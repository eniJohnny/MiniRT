/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_angle_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:43:14 by amorel            #+#    #+#             */
/*   Updated: 2022/12/01 18:51:00 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	check_angle(char *str)
{
	if (!str || ft_atod(str) <= 0 || ft_atod(str) >= (M_PI / 2))
		return (0);
	return (1);
}
