/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:17:53 by amorel            #+#    #+#             */
/*   Updated: 2022/11/16 13:24:35 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_closest_plane_hit(t_hit *hit, t_ray *ray, t_plane *list)
{
	double	old_t;
	t_plane	*current;

	current = list;
	while (current)
	{
		old_t = hit->t;
		hit_plane(hit, ray, current);
		if (old_t != hit->t)
		{
			hit->object = current;
			hit->type = PLANE;
		}
		current = current->next;
	}
}

void	hit_plane(t_hit *hit, t_ray *ray, t_plane *pln)
{
	double	t;
	t_vec	norm;
	double	normalized_dir;
	t_vec	oc;

	vector_sub(&oc, pln->pos, ray->pos);
	vector_copy(&norm, pln->dir);
	normalized_dir = dot_product(ray->dir, pln->dir);
	if (normalized_dir == 0.0)
		return ;
	if (normalized_dir > 0.0)
		vector_multiplication(-1.0, &norm);
	t = dot_product(&oc, pln->dir) / normalized_dir;
	if (t >= 0.0 && (hit->t < 0.0 || t < hit->t))
	{
		hit->t = t;
		vector_copy(&hit->norm, &norm);
	}
}
