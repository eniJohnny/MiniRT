/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:18:06 by amorel            #+#    #+#             */
/*   Updated: 2022/11/24 15:22:25 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_closest_cyl_hit(t_hit *hit, t_ray *ray, t_cylinder *lst)
{
	double		old_t;
	t_cylinder	*current;

	current = lst;
	while (current)
	{
		old_t = hit->t;
		hit_cylinder(hit, ray, current);
		if (old_t != hit->t)
		{
			hit->object = current;
			hit->type = CYLINDER;
		}
		current = current->next;
	}
}

static void	hit_cylinder_caps(t_ray *ray, t_cylinder *cyl, double *t)
{
	t_vec	oc;
	double	dot_sd;
	double	dot_ocd;

	vector_copy(&oc, cyl->dir);
	vector_multiplication(cyl->height / 2.0, &oc);
	vector_sum(&oc, cyl->pos, &oc);
	vector_sub(&oc, &oc, ray->pos);
	dot_sd = dot_product(ray->dir, cyl->dir);
	dot_ocd = dot_product(&oc, cyl->dir);
	t[2 + (dot_sd >= 0.0)] = (dot_ocd + cyl->height / 2.0) / dot_sd;
	t[2 + (dot_sd < 0.0)] = (dot_ocd - cyl->height / 2.0) / dot_sd;
}

static void	set_hit_parameters(t_hit *hit, t_ray *ray,
	t_cylinder *cyl, double *t)
{
	t_vec	oc;
	t_vec	op;
	double	ht;

	ht = fmax(t[0], t[2]);
	if (ht < 0.0)
		ht = fmin(t[1], t[3]);
	if (ht < 0.0 || (hit->t > 0.0 && ht > hit->t))
		return ;
	hit->t = ht;
	if (ht == t[2] || ht == t[3])
	{
		vector_copy(&hit->norm, cyl->dir);
		if (dot_product(ray->dir, cyl->dir) > 0.0)
			vector_multiplication(-1.0, &hit->norm);
		return ;
	}
	vector_multiplication(ht, vector_copy(&op, ray->dir));
	vector_sub(&oc, cyl->pos, ray->pos);
	vector_sub(&op, &op, &oc);
	vector_copy(&hit->norm, cyl->dir);
	vector_multiplication(dot_product(&op, cyl->dir), &hit->norm);
	vector_sub(&hit->norm, &op, &hit->norm);
	vector_normalize(&hit->norm);
}

void	hit_cylinder(t_hit *hit, t_ray *ray, t_cylinder *cyl)
{
	t_vec	sd;
	t_vec	cod;
	double	comp[4];
	double	t[4];
	double	radius;

	radius = cyl->diameter / 2.0;
	cross_product(&sd, ray->dir, cyl->dir);
	vector_sub(&cod, ray->pos, cyl->pos);
	cross_product(&cod, &cod, cyl->dir);
	comp[0] = dot_product(&sd, &sd);
	comp[1] = dot_product(&cod, &sd) * 2.0;
	comp[2] = dot_product(&cod, &cod) - (radius * radius);
	comp[3] = comp[1] * comp[1] - 4.0 * comp[0] * comp[2];
	if (comp[3] < 0.0)
		return ;
	comp[3] = sqrt(comp[3]);
	t[comp[0] >= 0.0] = (-comp[1] + comp[3]) / (2.0 * comp[0]);
	t[comp[0] < 0.0] = (-comp[1] - comp[3]) / (2.0 * comp[0]);
	hit_cylinder_caps(ray, cyl, (double *)t);
	if (t[2] > t[1] || t[3] < t[0])
		return ;
	set_hit_parameters(hit, ray, cyl, t);
}
