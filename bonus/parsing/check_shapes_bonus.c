/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shapes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:30:32 by amorel            #+#    #+#             */
/*   Updated: 2022/12/01 18:47:49 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	check_sphere(char **array)
{
	if (!array[1] || !check_vector_parsing(array[1], 0))
		return (0);
	else if (!array[2] || !check_size_parsing(array[2]))
		return (0);
	else if (!array[3] || !check_rgb_parsing(array[3]))
		return (0);
	return (1);
}

int	check_plane(char **array)
{
	if (!array[1] || !check_vector_parsing(array[1], 0))
		return (0);
	else if (!array[2] || !check_vector_parsing(array[2], 1))
		return (0);
	else if (!array[3] || !check_rgb_parsing(array[3]))
		return (0);
	return (1);
}

int	check_cylinder(char **array)
{
	if (!array[1] || !check_vector_parsing(array[1], 0))
		return (0);
	else if (!array[2] || !check_vector_parsing(array[2], 1))
		return (0);
	else if (!array[3] || !check_size_parsing(array[3]))
		return (0);
	else if (!array[4] || !check_size_parsing(array[4]))
		return (0);
	else if (!array[5] || !check_rgb_parsing(array[5]))
		return (0);
	return (1);
}

int	check_cone(char **array)
{
	if (!array[1] || !check_vector_parsing(array[1], 0))
		return (0);
	else if (!array[2] || !check_vector_parsing(array[2], 1))
		return (0);
	else if (!array[3] || !check_angle(array[3]))
		return (0);
	else if (!array[4] || !check_size_parsing(array[4]))
		return (0);
	else if (!array[5] || !check_rgb_parsing(array[5]))
		return (0);
	return (1);
}
