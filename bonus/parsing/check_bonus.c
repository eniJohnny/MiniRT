/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:34:17 by amorel            #+#    #+#             */
/*   Updated: 2022/11/30 17:02:35 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	check_amblight(char **array)
{
	if (!array[1] || !check_ratio_parsing(array[1]))
		return (0);
	else if (!array[2] || !check_rgb_parsing(array[2]))
		return (0);
	return (1);
}

int	check_light(char **array)
{
	if (!array[1] || !check_vector_parsing(array[1], 0))
		return (0);
	else if (!array[2] || !check_ratio_parsing(array[2]))
		return (0);
	else if (!array[3] || !check_rgb_parsing(array[3]))
		return (0);
	return (1);
}

int	check_camera(char **array)
{
	if (!array[1] || !check_vector_parsing(array[1], 0))
		return (0);
	else if (!array[2] || !check_vector_parsing(array[2], 1))
		return (0);
	else if (!array[3] || ft_atod(array[3]) < 0 || ft_atod(array[3]) > 180)
		return (0);
	return (1);
}
