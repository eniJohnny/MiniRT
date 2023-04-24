/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:36:29 by amorel            #+#    #+#             */
/*   Updated: 2022/11/16 23:45:10 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double	get_t(double a, double b, double d)
{
	double	t1;
	double	t2;
	double	tmp;

	t1 = (-b - sqrt(d)) / (2.0 * a);
	t2 = (-b + sqrt(d)) / (2.0 * a);
	tmp = t1;
	t1 = fmin(t1, t2);
	t2 = fmax(tmp, t2);
	if (t1 <= 0.0)
		return (t2);
	return (t1);
}

void	get_closest_sphere_hit(t_hit *closest, t_ray *ray, t_sphere *sph)
{
	double		old_t;
	t_sphere	*current;

	current = sph;
	while (current)
	{
		old_t = closest->t;
		hit_sphere(closest, ray, current);
		if (old_t != closest->t)
		{
			closest->type = SPHERE;
			closest->object = current;
		}
		current = current->next;
	}
}

void	hit_sphere(t_hit *hit, t_ray *ray, t_sphere *sph)
{
	double	t;
	t_vec	oc;
	double	vars[4];

	if (!sph || !ray || !hit)
		return ;
	vector_sub(&oc, ray->pos, sph->pos);
	vars[0] = dot_product(ray->dir, ray->dir);
	vars[1] = 2.0 * dot_product(&oc, ray->dir);
	vars[2] = dot_product(&oc, &oc) - pow((sph->diameter / 2), 2);
	vars[3] = (vars[1] * vars[1]) - (4.0 * vars[0] * vars[2]);
	if (vars[3] >= 0.0)
	{
		t = get_t(vars[0], vars[1], vars[3]);
		if (t > 0.0 && (hit->t < 0.0 || t < hit->t))
		{
			hit->t = t;
			vector_copy(&hit->norm, ray->dir);
			vector_multiplication(t, &hit->norm);
			vector_sum(&hit->norm, &hit->norm, ray->pos);
			vector_sub(&hit->norm, &hit->norm, sph->pos);
			vector_normalize(&hit->norm);
		}
	}
}
