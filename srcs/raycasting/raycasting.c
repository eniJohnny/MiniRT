/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:29:04 by johrober          #+#    #+#             */
/*   Updated: 2022/11/22 13:23:33 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	***gen_rays(t_camera *cam, t_vec *topl, t_vec *delta_x, t_vec *delta_y)
{
	t_ray	***rays;
	t_vec	tmp;
	int		x;
	int		y;

	rays = (t_ray ***)ft_tab_init(2, HEIGHT, WIDTH);
	if (!rays)
		return (NULL);
	y = -1;
	while (++y < HEIGHT)
	{
		vector_copy(&tmp, topl);
		x = -1;
		while (++x < WIDTH)
		{
			rays[y][x] = malloc(sizeof(t_ray));
			rays[y][x]->pos = cam->pos;
			rays[y][x]->hit_list = NULL;
			rays[y][x]->dir = vector_normalize(vector_allocated_copy(&tmp));
			rays[y][x]->debug = 0;
			vector_sum(&tmp, &tmp, delta_x);
		}
		vector_sum(topl, topl, delta_y);
	}
	return (rays);
}

t_ray	***get_camera_rays(t_camera *cam)
{
	t_vec	corners[3];
	t_vec	delta_x;
	t_vec	delta_y;
	t_vec	tmp;

	cam->z = vector_copy(cam->z, cam->dir);
	to_vector (&tmp, 0.0, 1.0, 0.01);
	cross_product(cam->x, cam->z, &tmp);
	vector_normalize(cam->x);
	cross_product(cam->y, cam->z, cam->x);
	vector_normalize(cam->y);
	get_corner_vectors(corners, cam);
	get_delta(&delta_x, &delta_y, corners);
	return (gen_rays(cam, corners, &delta_x, &delta_y));
}

void	get_closest_hit(t_hit *hit, t_program *p, t_ray *ray)
{
	hit->t = -1.0;
	hit->type = NONE;
	hit->object = NULL;
	get_closest_cyl_hit(hit, ray, p->cylinder);
	get_closest_sphere_hit(hit, ray, p->sphere);
	get_closest_plane_hit(hit, ray, p->plane);
	if (hit->t > 0.0)
	{
		vector_copy(&hit->pos, ray->dir);
		vector_multiplication(hit->t, &hit->pos);
		vector_sum(&hit->pos, &hit->pos, ray->pos);
	}
}

void	cast_single_ray(t_rgb *rgb, t_program *p, t_ray *ray)
{
	t_hit	*hit;

	hit = malloc(sizeof(t_hit));
	if (!hit)
		clean_exit(p, EXIT_FAILURE, "Fatal error\n");
	get_closest_hit(hit, p, ray);
	apply_lighting(rgb, p, hit, ray);
	free(hit);
}
