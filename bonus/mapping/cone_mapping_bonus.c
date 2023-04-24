/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_mapping_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:51:53 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 18:38:43 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_cone_unit_vectors(t_vec *uv, t_hit *hit)
{
	t_cone	*cne;
	t_vec	tmp;

	cne = (t_cone *)hit->object;
	if (dot_product(cne->dir, &hit->norm) < 0.0)
	{
		vector_sub(&uv[1], &hit->pos, cne->pos);
		vector_copy(&tmp, cne->dir);
		vector_multiplication(dot_product(&uv[1], cne->dir), &tmp);
		vector_normalize(vector_sub(&uv[1], &uv[1], &tmp));
		vector_normalize(cross_product(&uv[0], &uv[1], &hit->norm));
	}
	else
	{
		vector_sub(&uv[1], &hit->pos, cne->pos);
		vector_normalize(vector_multiplication(-1.0, &uv[1]));
		vector_normalize(cross_product(&uv[0], &uv[1], cne->dir));
	}
}

static double	get_projected_cone_y(t_vec *op, t_hit *hit, t_cone *cne)
{
	t_projection	proj;
	t_vec			tmp;

	proj.radius = tan(cne->angle) * cne->height;
	proj.hypo = cne->height / cos(cne->angle);
	proj.ratio = proj.hypo / (proj.radius + proj.hypo);
	if (dot_product(cne->dir, &hit->norm) < 0.98
		&& dot_product(cne->dir, &hit->norm) > -0.98)
	{
		vector_sub(op, &hit->pos, cne->pos);
		vector_copy(&tmp, cne->dir);
		proj.y = dot_product(op, cne->dir);
		vector_multiplication(proj.y, &tmp);
		proj.y = proj.y * proj.ratio / cne->height;
		vector_sub(op, op, &tmp);
	}
	else
	{
		vector_sub(op, &hit->pos, cne->pos);
		vector_copy(&tmp, cne->dir);
		vector_sub(op, op, vector_multiplication(cne->height, &tmp));
		proj.y = proj.ratio + (1.0 - (sqrt(dot_product(op, op)) \
			/ proj.radius)) * (1.0 - proj.ratio);
	}
	return (proj.y);
}

void	get_projected_cone_point(t_hit *hit, t_cone *cne, double *xy)
{
	t_vec	uv[2];
	t_vec	op;

	to_vector(&uv[0], 0, 0.0, 1.0);
	cross_product(&uv[0], cne->dir, &uv[0]);
	to_vector(&uv[1], 0, 1.0, 0.0);
	cross_product(&uv[1], cne->dir, &uv[1]);
	if (dot_product(&uv[1], &uv[1]) > dot_product(&uv[0], &uv[0]))
		vector_copy(&uv[0], &uv[1]);
	vector_normalize(cross_product(&uv[0], cne->dir, &uv[0]));
	vector_normalize(cross_product(&uv[1], cne->dir, &uv[0]));
	xy[1] = get_projected_cone_y(&op, hit, cne);
	vector_normalize(&op);
	xy[0] = acos(dot_product(&op, &uv[0]));
	if (dot_product(&op, &uv[1]) < 0.0)
		xy[0] = 2.0 * M_PI - xy[0];
	xy[0] /= (2.0 * M_PI);
}
