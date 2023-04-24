/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_mapping_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:09:00 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 15:25:15 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	get_normalized_uv(t_vec *uv, t_hit *hit, t_vec *op, double dn)
{
	t_cylinder	*cyl;

	cyl = hit->object;
	if (dn < 0.5 && dn > -0.5)
	{
		vector_normalize(cross_product(&uv[0], &hit->norm, cyl->dir));
		vector_normalize(cross_product(&uv[1], &hit->norm, &uv[0]));
	}
	else if (dn >= 0.5)
	{
		vector_multiplication(cyl->height, vector_copy(op, cyl->dir));
		vector_sub(op, &hit->pos, vector_sum(op, op, cyl->pos));
		vector_normalize(cross_product(&uv[0], op, cyl->dir));
		vector_normalize(vector_copy(&uv[1], op));
	}
	else
	{
		vector_sub(op, &hit->pos, cyl->pos);
		vector_normalize(cross_product(&uv[0], op, cyl->dir));
		vector_normalize(vector_copy(&uv[1], op));
	}
}

void	get_cylinder_unit_vectors(t_vec *uv, t_hit *hit)
{
	t_cylinder	*cyl;
	t_vec		op;
	double		dn;

	cyl = hit->object;
	dn = dot_product(cyl->dir, &hit->norm);
	get_normalized_uv(uv, hit, &op, dn);
	vector_multiplication(-1.0, &uv[0]);
	vector_multiplication(-1.0, &uv[1]);
}

void	get_checkered_cylinder_color(t_rgb *rgb, t_hit *hit, t_cylinder *cyl)
{
	double	xy[2];
	double	real_ratio;
	double	chk_ratio;
	int		chk_cyl[2];

	get_projected_cylinder_point(hit, cyl, (double *)xy);
	real_ratio = cyl->diameter * 0.5 / (cyl->diameter + cyl->height);
	chk_ratio = cyl->height / (cyl->diameter * M_PI);
	chk_cyl[0] = fmax((double)CHK_CYL * chk_ratio, 1.0);
	chk_ratio = cyl->diameter / fmax(cyl->height, 0.5);
	chk_cyl[1] = (double)chk_cyl[0] * chk_ratio / 2.0;
	chk_ratio = (double)chk_cyl[1] / (double)(chk_cyl[1] * 2 + chk_cyl[0]);
	xy[0] *= (double)CHK_CYL;
	if (xy[1] <= real_ratio)
		xy[1] = xy[1] * chk_ratio / real_ratio;
	else if (xy[1] >= 1.0 - real_ratio)
		xy[1] = 1.0 - ((1.0 - xy[1]) * chk_ratio / real_ratio);
	else
		xy[1] = chk_ratio + ((xy[1] - real_ratio) \
			* (1.0 - 2.0 * chk_ratio) / (1.0 - 2.0 * real_ratio));
	xy[1] *= (double)(chk_cyl[1] * 2 + chk_cyl[0]);
	if ((int)(floor(xy[0]) + floor(xy[1])) % 2 == 0)
		to_rgb(rgb, 0.1, 0.1, 0.1);
	else
		copy_rgb(rgb, cyl->rgb);
}

void	get_cylinder_color(t_rgb *rgb, t_program *p,
		t_hit *hit, t_cylinder *cyl)
{
	if (cyl->bump == -1)
		copy_rgb(rgb, cyl->rgb);
	else if (cyl->bump == -2)
		get_checkered_cylinder_color(rgb, hit, cyl);
	else if (cyl->bump < p->gui->texture_nb)
		get_texture_color(rgb, p, hit);
	else
		copy_rgb(rgb, cyl->rgb);
}
