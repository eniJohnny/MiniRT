/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:12:48 by johrober          #+#    #+#             */
/*   Updated: 2022/11/16 23:44:57 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	get_hit_type(t_ray *ray, t_cone *cne, double *t)
{
	if (is_shadow_cone(t[0], ray, cne) && !is_shadow_cone(t[1], ray, cne))
	{
		if (t[1] > t[3])
			return (-1);
		return (0);
	}
	else if (!is_shadow_cone(t[0], ray, cne) && is_shadow_cone(t[1], ray, cne))
	{
		if (t[0] < t[2])
			return (-1);
		return (1);
	}
	else
	{
		if (t[1] < t[2] || t[3] < t[0])
			return (-1);
		return (2);
	}
	return (-1);
}

double	get_real_t(int type, double *t)
{
	if (type == 0)
	{
		if (t[1] > 0.0)
			return (t[1]);
		return (t[3]);
	}
	else if (type == 1)
	{
		if (t[2] > 0.0)
			return (t[2]);
		return (t[0]);
	}
	else if (type == 2)
	{
		if (fmax(t[0], t[2]) < 0.0)
			return (fmin(t[1], t[3]));
		return (fmax(t[0], t[2]));
	}
	return (-1.0);
}

void	get_cone_quadratic(double *cmp, t_ray *ray, t_cone *cne)
{
	double	rdcd;
	t_vec	co;
	double	cod;
	double	cost;

	cost = cos(cne->angle);
	vector_sub(&co, ray->pos, cne->pos);
	rdcd = dot_product(ray->dir, cne->dir);
	cod = dot_product(&co, cne->dir);
	cmp[0] = rdcd * rdcd - cost * cost;
	cmp[1] = 2.0 * (rdcd * cod - dot_product(ray->dir, &co) * cost * cost);
	cmp[2] = cod * cod - dot_product(&co, &co) * cost * cost;
	cmp[3] = cmp[1] * cmp[1] - 4.0 * cmp[0] * cmp[2];
}

int	is_shadow_cone(double t, t_ray *ray, t_cone *cne)
{
	t_vec	cp;

	vector_multiplication(t, vector_copy(&cp, ray->dir));
	vector_sum(&cp, &cp, ray->pos);
	vector_sub(&cp, &cp, cne->pos);
	return (dot_product(&cp, cne->dir) < 0.0);
}
