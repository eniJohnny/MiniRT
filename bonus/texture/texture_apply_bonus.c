/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_apply_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:44:16 by johrober          #+#    #+#             */
/*   Updated: 2022/12/05 16:41:09 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	get_texture_id(t_hit *hit)
{
	if (hit->type == SPHERE)
		return (((t_sphere *)hit->object)->bump);
	else if (hit->type == CYLINDER)
		return (((t_cylinder *)hit->object)->bump);
	else if (hit->type == PLANE)
		return (((t_plane *)hit->object)->bump);
	else if (hit->type == CONE)
		return (((t_cone *)hit->object)->bump);
	return (-1);
}

static	void	get_pos_color(t_rgb *rgb, int x, int y, t_img *texture)
{
	int		buf_index;

	buf_index = y * texture->l_bits + x * 4;
	if (texture->endian == 0)
	{
		rgb->r = (double)texture->buf[buf_index + 2] / 255.0;
		rgb->g = (double)texture->buf[buf_index + 1] / 255.0;
		rgb->b = (double)texture->buf[buf_index + 0] / 255.0;
	}
	else
	{
		rgb->r = (double)texture->buf[buf_index + 1] / 255.0;
		rgb->g = (double)texture->buf[buf_index + 2] / 255.0;
		rgb->b = (double)texture->buf[buf_index + 3] / 255.0;
	}
}

void	get_texture_color(t_rgb *rgb, t_program *p, t_hit *hit)
{
	double	xy[2];
	int		texture_id;
	t_img	*texture;
	int		x;
	int		y;

	texture_id = get_texture_id(hit);
	get_projected_point(hit, (double *)xy);
	texture = p->textures[texture_id];
	x = xy[0] * ((double)texture->width - 1);
	y = xy[1] * ((double)texture->height - 1);
	get_pos_color(rgb, x, y, texture);
}
