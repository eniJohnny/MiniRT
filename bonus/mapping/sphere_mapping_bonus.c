/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_mapping_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:56:52 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 17:54:36 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_projected_sphere_point(t_hit *hit, double *xy)
{
	double	theta;
	double	phi;

	theta = atan2(hit->norm.x, hit->norm.z) / (2.0 * M_PI);
	theta = 1.0 - (theta + 0.5);
	phi = acos(hit->norm.y) / M_PI;
	phi = 1.0 - phi;
	xy[0] = theta;
	xy[1] = phi;
}

void	get_checkered_sphere_color(t_rgb *rgb, t_hit *hit, t_sphere *sphere)
{
	double	xy[2];

	get_projected_sphere_point(hit, (double *)xy);
	xy[0] *= (double)CHK_SPH;
	xy[1] *= (double)CHK_SPH / 2.0;
	if ((int)(floor(xy[0]) + floor(xy[1])) % 2 == 0)
		to_rgb(rgb, 0.9, 0.9, 0.9);
	else
		copy_rgb(rgb, sphere->rgb);
}

void	get_sphere_color(t_rgb *rgb, t_program *p, t_hit *hit, t_sphere *sph)
{
	if (sph->bump == -1)
		copy_rgb(rgb, sph->rgb);
	else if (sph->bump == -2)
		get_checkered_sphere_color(rgb, hit, sph);
	else if (sph->bump >= 0 && sph->bump < p->gui->texture_nb)
		get_texture_color(rgb, p, hit);
	else
		copy_rgb(rgb, sph->rgb);
}

void	get_sphere_unit_vectors(t_vec *uv, t_hit *hit)
{
	cross_product(&uv[0], to_vector(&uv[0], 0.0, 1.0, 0.0), &hit->norm);
	cross_product(&uv[1], &hit->norm, &uv[0]);
	vector_normalize(&uv[0]);
	vector_normalize(&uv[1]);
	vector_multiplication(-1.0, &uv[0]);
	vector_multiplication(-1.0, &uv[1]);
}
