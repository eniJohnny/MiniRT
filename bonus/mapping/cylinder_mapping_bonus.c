/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:25:56 by johrober          #+#    #+#             */
/*   Updated: 2022/11/14 17:35:14 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double	get_checkered_cap_ratio(t_cylinder *cyl, t_vec *op)
{
	double	ratio;

	ratio = sqrt(dot_product(op, op));
	vector_multiplication(1.0 / ratio, op);
	return (ratio * 2.0 / (cyl->diameter));
}

static double	get_projected_cylinder_y(t_vec *op, t_hit *hit, \
	t_cylinder *cyl, double ratio)
{
	double	y;
	double	dn;

	dn = dot_product(cyl->dir, &hit->norm);
	if (dn > 0.5)
	{
		vector_copy(op, cyl->dir);
		vector_multiplication(cyl->height, op);
		vector_sum(op, op, cyl->pos);
		vector_sub(op, &hit->pos, op);
		y = 1.0 - (get_checkered_cap_ratio(cyl, op)) * ratio;
	}
	else if (dn < -0.5)
	{
		vector_sub(op, &hit->pos, cyl->pos);
		y = get_checkered_cap_ratio(cyl, op) * ratio;
	}
	else
	{
		vector_sub(op, &hit->pos, cyl->pos);
		y = ratio + dot_product(op, cyl->dir) * \
			(1.0 - 2.0 * ratio) / cyl->height;
		vector_copy(op, &hit->norm);
	}
	return (y);
}

void	get_projected_cylinder_point(t_hit *hit, t_cylinder *cyl, double *xy)
{
	t_vec		op;
	t_vec		uv[2];
	double		ratio;

	to_vector(&uv[0], 0, 0.0, 1.0);
	cross_product(&uv[0], cyl->dir, &uv[0]);
	to_vector(&uv[1], 0, 1.0, 0.0);
	cross_product(&uv[1], cyl->dir, &uv[1]);
	if (dot_product(&uv[1], &uv[1]) > dot_product(&uv[0], &uv[0]))
		vector_copy(&uv[0], &uv[1]);
	vector_normalize(cross_product(&uv[0], cyl->dir, &uv[0]));
	vector_normalize(cross_product(&uv[1], cyl->dir, &uv[0]));
	ratio = cyl->diameter * 0.5 / (cyl->diameter + cyl->height);
	xy[1] = get_projected_cylinder_y(&op, hit, cyl, ratio);
	xy[0] = acos(dot_product(&op, &uv[0]));
	if (dot_product(&op, &uv[1]) < 0.0)
		xy[0] = 2.0 * M_PI - xy[0];
	xy[0] /= (2.0 * M_PI);
}
