/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:03:46 by johrober          #+#    #+#             */
/*   Updated: 2022/12/05 17:36:27 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_bumpmap	*get_bumpmap(t_program *p, t_hit *hit)
{
	int	bump;

	bump = -1;
	if (hit->type == SPHERE)
		bump = ((t_sphere *)hit->object)->bump;
	else if (hit->type == PLANE)
		bump = ((t_plane *)hit->object)->bump;
	else if (hit->type == CYLINDER)
		bump = ((t_cylinder *)hit->object)->bump;
	else if (hit->type == CONE)
		bump = ((t_cone *)hit->object)->bump;
	if (bump >= 0)
		return (p->bm[bump]);
	return (NULL);
}

void	get_projected_point(t_hit *hit, double *xy)
{
	int	mod;

	if (hit->type == SPHERE)
		get_projected_sphere_point(hit, xy);
	else if (hit->type == CYLINDER)
		get_projected_cylinder_point(hit, hit->object, xy);
	else if (hit->type == CONE)
		get_projected_cone_point(hit, hit->object, xy);
	else if (hit->type == PLANE)
	{
		get_projected_plane_point(hit, hit->object, xy);
		mod = xy[0] / TEXTURE_SIZE;
		xy[0] -= ((double)mod * TEXTURE_SIZE);
		if (xy[0] < 0.0)
			xy[0] += TEXTURE_SIZE;
		xy[0] /= (TEXTURE_SIZE);
		mod = xy[1] / TEXTURE_SIZE;
		xy[1] -= ((double)mod * TEXTURE_SIZE);
		if (xy[1] < 0.0)
			xy[1] += TEXTURE_SIZE;
		xy[1] /= (TEXTURE_SIZE);
	}
}

static void	free_bm_map(double **map, int nb)
{
	int	i;

	i = -1;
	while (++i < nb && map[i])
		free(map[i]);
	free(map);
}

void	free_bumpmap_list(t_program *p)
{
	int	i;

	i = -1;
	if (!p->gui || !p->gui->bump_names)
		return ;
	while (++i < p->gui->bump_nb)
	{
		free(p->gui->bump_names[i]);
		free_bm_map(p->bm[i]->map, p->bm[i]->img->width);
		mlx_destroy_image(p->mlx, p->bm[i]->img->image);
		free(p->bm[i]->img);
		free(p->bm[i]);
	}
	free(p->gui->bump_names);
	free(p->bm);
}
