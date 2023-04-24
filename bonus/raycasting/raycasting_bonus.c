/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:29:04 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 16:48:06 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	gen_rays(t_program *p, t_vec *topl, t_vec *delta_x, t_vec *delta_y)
{
	t_ray	***rays;
	t_vec	tmp;
	int		x;
	int		y;

	rays = p->rays;
	y = -1;
	while (++y < HEIGHT)
	{
		vector_copy(&tmp, topl);
		x = -1;
		while (++x < WIDTH)
		{
			rays[y][x]->pos = p->camera->pos;
			vector_normalize(vector_copy(rays[y][x]->dir, &tmp));
			rays[y][x]->debug = 0;
			vector_sum(&tmp, &tmp, delta_x);
		}
		vector_sum(topl, topl, delta_y);
	}
}

void	get_camera_rays(t_program *p)
{
	t_vec	corners[3];
	t_vec	delta_x;
	t_vec	delta_y;
	t_vec	tmp;

	p->camera->z = vector_copy(p->camera->z, p->camera->dir);
	to_vector (&tmp, 0.0, 1.0, 0.01);
	cross_product(p->camera->x, p->camera->z, &tmp);
	vector_normalize(p->camera->x);
	cross_product(p->camera->y, p->camera->z, p->camera->x);
	vector_normalize(p->camera->y);
	get_corner_vectors(corners, p->camera);
	get_delta(&delta_x, &delta_y, corners);
	return (gen_rays(p, &(corners[0]), &delta_x, &delta_y));
}

void	get_closest_hit(t_hit *hit, t_program *p, t_ray *ray)
{
	hit->t = -1.0;
	hit->type = NONE;
	hit->object = NULL;
	get_closest_cyl_hit(hit, ray, p->cylinder);
	get_closest_sphere_hit(hit, ray, p->sphere);
	get_closest_plane_hit(hit, ray, p->plane);
	get_closest_con_hit(hit, ray, p->cone);
	if (hit->t > 0.0)
	{
		vector_copy(&hit->pos, ray->dir);
		vector_multiplication(hit->t, &hit->pos);
		vector_sum(&hit->pos, &hit->pos, ray->pos);
	}
}

void	cast_single_ray(t_rgb *rgb, t_program *p, t_ray *ray)
{
	t_hit	hit;

	get_closest_hit(&hit, p, ray);
	apply_lighting(rgb, p, &hit, ray);
}
