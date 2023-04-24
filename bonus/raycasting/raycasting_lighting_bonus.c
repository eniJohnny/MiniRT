/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_lighting_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:10:30 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 16:20:25 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
	t_vec	norm;

	vector_sub(&to_spot, l->pos, &h->pos);
	dist_ratio = sqrt(dot_product(&to_spot, &to_spot));
	if (is_light_obstructed(p, &to_spot, h, r))
		return (0.0);
	apply_bumpmap_to_norm(&norm, h, get_bumpmap(p, h));
	if (dot_product(&norm, r->dir) > 0.0)
		vector_multiplication(-1.0, &norm);
	light = dot_product(&norm, &to_spot);
	if (light < 0.0)
		return (0.0);
	vector_reflect(&to_spot, &to_spot, &norm);
	vector_multiplication(-1.0, &to_spot);
	dist_ratio = fmax(1.0 - (dist_ratio * dist_ratio)
			/ pow(LIGHT_RANGE, 2), 0.0);
	light += pow(dot_product(&to_spot, r->dir), SPEC_SHN) * SPEC_STR;
	return (light * l->ratio * dist_ratio);
}

static void	get_light_color(t_rgb *res, t_program *p, t_hit *hit, t_ray *ray)
{
	t_light	*current;
	double	ratio;

	res->r = p->amblight->rgb->r * p->amblight->ratio;
	res->g = p->amblight->rgb->g * p->amblight->ratio;
	res->b = p->amblight->rgb->b * p->amblight->ratio;
	current = p->light;
	while (current)
	{
		ratio = get_light_ratio(p, current, hit, ray);
		res->r += current->rgb->r * ratio;
		res->g += current->rgb->g * ratio;
		res->b += current->rgb->b * ratio;
		current = current->next;
	}
	res->r = fmin(res->r, 1.0);
	res->g = fmin(res->g, 1.0);
	res->b = fmin(res->b, 1.0);
}

static void	get_object_color(t_rgb *rgb, t_program *p, t_hit *hit)
{
	if (hit->type == SPHERE)
		get_sphere_color(rgb, p, hit, hit->object);
	else if (hit->type == CYLINDER)
		get_cylinder_color(rgb, p, hit, hit->object);
	else if (hit->type == PLANE)
		get_plane_color(rgb, p, hit, hit->object);
	else if (hit->type == CONE)
		get_cone_color(rgb, p, hit, hit->object);
}

void	apply_lighting(t_rgb *rgb, t_program *p, t_hit *hit, t_ray *ray)
{
	t_rgb	light_rgb;

	if (hit->t > 0.0)
	{
		get_object_color(rgb, p, hit);
		if (dot_product(&hit->norm, ray->dir) > 0.0)
			vector_multiplication(-1.0, &hit->norm);
		if (hit->type != NONE)
			get_light_color(&light_rgb, p, hit, ray);
		blend_colors(rgb, &light_rgb);
	}
	else
		to_rgb(rgb, 0, 0, 0);
}
