/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:03:57 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 16:20:56 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_closest_con_hit(t_hit *hit, t_ray *ray, t_cone *lst)
{
	double	old_t;
	t_cone	*current;

	current = lst;
	while (current)
	{
		old_t = hit->t;
		hit_cone(hit, ray, current);
		if (old_t != hit->t)
		{
			hit->object = current;
			hit->type = CONE;
		}
		current = current->next;
	}
}

static void	hit_cone_caps(t_ray *ray, t_cone *cne, double *t)
{
	t_vec	oc;
	double	dot_sd;
	double	dot_ocd;

	vector_copy(&oc, cne->dir);
	vector_multiplication(cne->height / 2.0, &oc);
	vector_sum(&oc, cne->pos, &oc);
	vector_sub(&oc, &oc, ray->pos);
	dot_sd = dot_product(ray->dir, cne->dir);
	dot_ocd = dot_product(&oc, cne->dir);
	t[2 + (dot_sd >= 0.0)] = (dot_ocd + cne->height / 2.0) / dot_sd;
	t[2 + (dot_sd < 0.0)] = (dot_ocd - cne->height / 2.0) / dot_sd;
}

static void	set_cone_hit(t_hit *hit, t_ray *ray, t_cone *cne, double *t)
{
	double	ht;
	t_vec	cp;
	int		type;

	type = get_hit_type(ray, cne, t);
	ht = get_real_t(type, t);
	if (type == -1 || ht < 0.0 || (hit->t > 0.0 && ht > hit->t))
		return ;
	hit->t = ht;
	if (ht == t[2] || ht == t[3])
	{
		vector_copy(&hit->norm, cne->dir);
		vector_multiplication(-1.0, &hit->norm);
		return ;
	}
	vector_multiplication(ht, vector_copy(&cp, ray->dir));
	vector_sum(&cp, &cp, ray->pos);
	vector_sub(&cp, &cp, cne->pos);
	cross_product(&hit->norm, &cp, cne->dir);
	cross_product(&hit->norm, &cp, &hit->norm);
	vector_normalize(&hit->norm);
}

void	hit_cone(t_hit *hit, t_ray *ray, t_cone *cne)
{
	double	cmp[4];
	double	t[4];

	get_cone_quadratic((double *)cmp, ray, cne);
	if (cmp[3] <= 0.0)
		return ;
	cmp[3] = sqrt(cmp[3]);
	t[cmp[0] >= 0.0] = (-cmp[1] + cmp[3]) / (2.0 * cmp[0]);
	t[cmp[0] < 0.0] = (-cmp[1] - cmp[3]) / (2.0 * cmp[0]);
	if (is_shadow_cone(t[0], ray, cne) && is_shadow_cone(t[1], ray, cne))
		return ;
	hit_cone_caps(ray, cne, (double *)t);
	set_cone_hit(hit, ray, cne, t);
}
