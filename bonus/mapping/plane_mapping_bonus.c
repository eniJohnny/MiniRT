/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:59:30 by johrober          #+#    #+#             */
/*   Updated: 2022/11/25 16:26:40 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_plane_unit_vectors(t_vec *uv, t_hit *hit)
{
	to_vector(&uv[0], 1.0, 0.0, 0.0);
	to_vector(&uv[1], 0.0, 1.0, 0.0);
	cross_product(&uv[0], &hit->norm, &uv[0]);
	cross_product(&uv[1], &hit->norm, &uv[1]);
	if (dot_product(&uv[1], &uv[1]) > dot_product(&uv[0], &uv[0]))
		vector_copy(&uv[0], &uv[1]);
	cross_product(&uv[1], &hit->norm, &uv[0]);
	vector_normalize(&uv[0]);
	vector_normalize(&uv[1]);
}

void	get_projected_plane_point(t_hit *hit, t_plane *pln, double *xy)
{
	t_vec	u;
	t_vec	v;
	t_vec	op;

	to_vector(&u, 1.0, 0.0, 0.0);
	to_vector(&v, 0.0, 1.0, 0.0);
	cross_product(&u, &hit->norm, &u);
	cross_product(&v, &hit->norm, &v);
	if (dot_product(&v, &v) > dot_product(&u, &u))
		vector_copy(&u, &v);
	cross_product(&v, &hit->norm, &u);
	vector_normalize(&u);
	vector_normalize(&v);
	vector_sub(&op, &hit->pos, pln->pos);
	xy[0] = dot_product(&op, &u);
	xy[1] = dot_product(&op, &v);
}

void	get_checkered_plane_color(t_rgb *rgb, t_hit *hit, t_plane *pln)
{
	double	xy[2];

	get_projected_plane_point(hit, pln, (double *)xy);
	if ((int)(floor(xy[0]) + floor(xy[1])) % 2 == 0)
		to_rgb(rgb, 0.1, 0.1, 0.1);
	else
		copy_rgb(rgb, pln->rgb);
}

void	get_plane_color(t_rgb *rgb, t_program *p, t_hit *hit, t_plane *pln)
{
	if (pln->bump == -1)
		copy_rgb(rgb, pln->rgb);
	else if (pln->bump == -2)
		get_checkered_plane_color(rgb, hit, pln);
	else if (pln->bump > 0 && pln->bump < p->gui->texture_nb)
		get_texture_color(rgb, p, hit);
	else
		copy_rgb(rgb, pln->rgb);
}
