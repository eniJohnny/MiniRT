/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_lighting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:40:53 by amorel            #+#    #+#             */
/*   Updated: 2022/11/26 16:54:37 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_light_obstructed(t_program *p,
	t_vec *to_spot, t_hit *h, t_ray *r)
{
	t_vec	pos;
	t_hit	spot_hit;
	t_ray	ray_to_spot;
	double	distance;

	distance = sqrt(dot_product(to_spot, to_spot));
	vector_normalize(to_spot);
	ray_to_spot.dir = to_spot;
	ray_to_spot.debug = r->debug;
	ray_to_spot.pos = vector_multiplication(0.001, vector_copy(&pos, to_spot));
	vector_sum(&pos, &pos, &h->pos);
	ray_to_spot.hit_list = NULL;
	get_closest_hit(&spot_hit, p, &ray_to_spot);
	if (spot_hit.t > 0.0 && spot_hit.t < distance)
		return (1);
	return (0);
}

static double	get_light_ratio(t_program *p, t_light *l, t_hit *h, t_ray *r)
{
	double	light;
	double	dist_ratio;
	t_vec	to_spot;

	vector_sub(&to_spot, l->pos, &h->pos);
	dist_ratio = sqrt(dot_product(&to_spot, &to_spot));
	if (is_light_obstructed(p, &to_spot, h, r))
		return (0.0);
	light = dot_product(&h->norm, &to_spot);
	if (light < 0.0)
		return (0.0);
	vector_reflect(&to_spot, &to_spot, &h->norm);
	vector_multiplication(-1.0, &to_spot);
	dist_ratio = fmax(1.0 - (dist_ratio * dist_ratio) \
		/ pow(LIGHT_RANGE, 2), 0.0);
	light += pow(dot_product(&to_spot, r->dir), SPEC_SHN) * SPEC_STR;
	return (light * l->ratio * dist_ratio);
}

static void	get_light_color(t_rgb *res, t_program *p, t_hit *hit, t_ray *ray)
{
	double	ratio;

	res->r = p->amblight->rgb->r * p->amblight->ratio;
	res->g = p->amblight->rgb->g * p->amblight->ratio;
	res->b = p->amblight->rgb->b * p->amblight->ratio;
	ratio = get_light_ratio(p, p->light, hit, ray);
	res->r += p->light->rgb->r * ratio;
	res->g += p->light->rgb->g * ratio;
	res->b += p->light->rgb->b * ratio;
	res->r = fmin(res->r, 1.0);
	res->g = fmin(res->g, 1.0);
	res->b = fmin(res->b, 1.0);
}

static void	get_object_color(t_rgb *rgb, t_hit *hit)
{
	if (hit->type == SPHERE)
		copy_rgb(rgb, ((t_sphere *)hit->object)->rgb);
	else if (hit->type == CYLINDER)
		copy_rgb(rgb, ((t_cylinder *)hit->object)->rgb);
	else if (hit->type == PLANE)
		copy_rgb(rgb, ((t_plane *)hit->object)->rgb);
}

void	apply_lighting(t_rgb *rgb, t_program *p, t_hit *hit, t_ray *ray)
{
	t_rgb	light_rgb;

	if (hit->t > 0.0)
	{
		if (hit->type != NONE)
			get_light_color(&light_rgb, p, hit, ray);
		get_object_color(rgb, hit);
		blend_colors(rgb, &light_rgb);
	}
	else
		to_rgb(rgb, 0, 0, 0);
}
