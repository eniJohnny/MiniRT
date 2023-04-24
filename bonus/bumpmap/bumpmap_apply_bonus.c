/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap_apply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:02:11 by johrober          #+#    #+#             */
/*   Updated: 2022/11/16 12:15:10 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	get_unit_vectors(t_vec *uv, t_hit *hit)
{
	if (hit->type == SPHERE)
		get_sphere_unit_vectors(uv, hit);
	else if (hit->type == CYLINDER)
		get_cylinder_unit_vectors(uv, hit);
	else if (hit->type == PLANE)
		get_plane_unit_vectors(uv, hit);
	else if (hit->type == CONE)
		get_cone_unit_vectors(uv, hit);
}

static void	get_bumpmap_norm(t_vec *norm, int x, int y, t_bumpmap *bm)
{
	int		buf_index;

	buf_index = y * bm->img->l_bits + x * 4;
	if (bm->img->endian == 0)
	{
		norm->x = (double)bm->img->buf[buf_index + 2] * 2.0 / 255.0 - 1.0;
		norm->y = (double)bm->img->buf[buf_index + 1] * 2.0 / 255.0 - 1.0;
		norm->z = (double)bm->img->buf[buf_index + 0] * 2.0 / 255.0 - 1.0;
	}
	else
	{
		norm->x = (double)bm->img->buf[buf_index + 1] * 2.0 / 255.0 - 1.0;
		norm->y = (double)bm->img->buf[buf_index + 2] * 2.0 / 255.0 - 1.0;
		norm->z = (double)bm->img->buf[buf_index + 3] * 2.0 / 255.0 - 1.0;
	}
}

static void	get_normal_map_norm(t_vec *norm, t_hit *hit, t_bumpmap *bm, int *xy)
{
	t_vec		uv[2];
	t_vec		xyz[3];
	double		comp[3];

	get_unit_vectors((t_vec *)uv, hit);
	vector_normalize(&uv[0]);
	vector_normalize(&uv[1]);
	get_bumpmap_norm(norm, xy[0], xy[1], bm);
	to_vector(&xyz[0], 1, 0, 0);
	to_vector(&xyz[1], 0, 1, 0);
	to_vector(&xyz[2], 0, 0, 1);
	comp[0] = dot_product(norm, &xyz[0]);
	comp[1] = dot_product(norm, &xyz[1]);
	comp[2] = dot_product(norm, &xyz[2]);
	vector_multiplication(comp[0], vector_copy(&xyz[0], &uv[0]));
	vector_multiplication(comp[1], vector_copy(&xyz[1], &uv[1]));
	vector_multiplication(comp[2], vector_copy(&xyz[2], &hit->norm));
	vector_sum(norm, vector_sum(norm, &xyz[0], &xyz[1]), &xyz[2]);
	vector_normalize(norm);
}

void	apply_bumpmap_to_norm(t_vec *norm, t_hit *hit, t_bumpmap *bm)
{
	double	xy[2];
	int		xy_int[2];

	if (!bm)
	{
		vector_copy(norm, &hit->norm);
		return ;
	}
	get_projected_point(hit, (double *)xy);
	xy_int[0] = xy[0] * ((double)bm->img->width);
	xy_int[1] = xy[1] * ((double)bm->img->height);
	if (xy_int[0] < 0)
		xy_int[0] = 0;
	get_normal_map_norm(norm, hit, bm, (int *)xy_int);
}
