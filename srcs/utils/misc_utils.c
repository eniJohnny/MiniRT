/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:56:17 by johrober          #+#    #+#             */
/*   Updated: 2022/11/18 17:35:13 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	copy_rgb(t_rgb *map, t_rgb *cpy)
{
	map->r = cpy->r;
	map->g = cpy->g;
	map->b = cpy->b;
}

void	blend_colors(t_rgb *color1, t_rgb *color2)
{
	color1->r = color1->r * color2->r;
	if (color1->r > 1.0)
		color1->r = 1.0;
	color1->g = color1->g * color2->g;
	if (color1->g > 1.0)
		color1->g = 1.0;
	color1->b = color1->b * color2->b;
	if (color1->b > 1.0)
		color1->b = 1.0;
}

double	get_distance(t_vec *p1, t_vec *p2)
{
	double	x;
	double	y;
	double	z;

	x = pow(p1->x - p2->x, 2);
	y = pow(p1->y - p2->y, 2);
	z = pow(p1->z - p2->z, 2);
	return (sqrt(x + y + z));
}
