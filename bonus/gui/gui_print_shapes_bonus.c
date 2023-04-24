/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_print_shapes_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:36:32 by amorel            #+#    #+#             */
/*   Updated: 2022/12/01 16:57:55 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	print_sphere(t_program *p, t_hit *hit)
{
	t_sphere	*sph;
	char		*str;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_sphere_imgs(p->mlx, p->gui);
	sph = (t_sphere *)(hit->object);
	str = NULL;
	print_to_gui(p, sph->diameter, 151, 81);
	print_to_gui(p, sph->pos->x, 116, 110);
	print_to_gui(p, sph->pos->y, 116, 134);
	print_to_gui(p, sph->pos->z, 116, 158);
	print_to_gui(p, sph->rgb->r, 76, 190);
	print_to_gui(p, sph->rgb->g, 76, 214);
	print_to_gui(p, sph->rgb->b, 76, 238);
		str = "none";
	if (sph->bump >= 0)
		str = p->gui->bump_names[sph->bump];
	else if (sph->bump == -2)
		str = "checkerboard";
	mlx_string_put(p->mlx, p->gui->win, 105, 755, WHITE, str);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}

void	print_cylinder(t_program *p, t_hit *hit)
{
	char		*str;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_cylinder_imgs(p->mlx, p->gui);
	print_to_gui(p, ((t_cylinder *)hit->object)->diameter, 151, 81);
	print_to_gui(p, ((t_cylinder *)hit->object)->height, 122, 111);
	print_to_gui(p, ((t_cylinder *)hit->object)->pos->x, 116, 140);
	print_to_gui(p, ((t_cylinder *)hit->object)->pos->y, 116, 164);
	print_to_gui(p, ((t_cylinder *)hit->object)->pos->z, 116, 188);
	print_to_gui(p, ((t_cylinder *)hit->object)->dir->x, 116, 233);
	print_to_gui(p, ((t_cylinder *)hit->object)->dir->y, 116, 257);
	print_to_gui(p, ((t_cylinder *)hit->object)->dir->z, 116, 281);
	print_to_gui(p, ((t_cylinder *)hit->object)->rgb->r, 76, 326);
	print_to_gui(p, ((t_cylinder *)hit->object)->rgb->g, 76, 350);
	print_to_gui(p, ((t_cylinder *)hit->object)->rgb->b, 76, 374);
	str = "none";
	if (((t_cylinder *)hit->object)->bump >= 0)
		str = p->gui->bump_names[((t_cylinder *)hit->object)->bump];
	else if (((t_cylinder *)hit->object)->bump == -2)
		str = "checkerboard";
	mlx_string_put(p->mlx, p->gui->win, 105, 755, WHITE, str);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}

void	print_cone(t_program *p, t_hit *hit)
{
	char	*str;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_cone_imgs(p->mlx, p->gui);
	print_to_gui(p, ((t_cone *)hit->object)->angle, 113, 81);
	print_to_gui(p, ((t_cone *)hit->object)->height, 122, 111);
	print_to_gui(p, ((t_cone *)hit->object)->pos->x, 116, 140);
	print_to_gui(p, ((t_cone *)hit->object)->pos->y, 116, 164);
	print_to_gui(p, ((t_cone *)hit->object)->pos->z, 116, 188);
	print_to_gui(p, ((t_cone *)hit->object)->dir->x, 116, 233);
	print_to_gui(p, ((t_cone *)hit->object)->dir->y, 116, 257);
	print_to_gui(p, ((t_cone *)hit->object)->dir->z, 116, 281);
	print_to_gui(p, ((t_cone *)hit->object)->rgb->r, 76, 326);
	print_to_gui(p, ((t_cone *)hit->object)->rgb->g, 76, 350);
	print_to_gui(p, ((t_cone *)hit->object)->rgb->b, 76, 374);
	str = "none";
	if (((t_cone *)hit->object)->bump >= 0)
		str = p->gui->bump_names[((t_cone *)hit->object)->bump];
	else if (((t_cone *)hit->object)->bump == -2)
		str = "checkerboard";
	mlx_string_put(p->mlx, p->gui->win, 105, 755, WHITE, str);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}

void	print_plane(t_program *p, t_hit *hit)
{
	t_plane	*pln;
	char	*str;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_plane_imgs(p->mlx, p->gui);
	pln = (t_plane *)(hit->object);
	print_to_gui(p, pln->pos->x, 116, 81);
	print_to_gui(p, pln->pos->y, 116, 105);
	print_to_gui(p, pln->pos->z, 116, 129);
	print_to_gui(p, pln->dir->x, 116, 174);
	print_to_gui(p, pln->dir->y, 116, 198);
	print_to_gui(p, pln->dir->z, 116, 222);
	print_to_gui(p, pln->rgb->r, 76, 267);
	print_to_gui(p, pln->rgb->g, 76, 291);
	print_to_gui(p, pln->rgb->b, 76, 315);
	str = "none";
	if (pln->bump >= 0)
		str = p->gui->bump_names[pln->bump];
	else if (((t_plane *)hit->object)->bump == -2)
		str = "checkerboard";
	mlx_string_put(p->mlx, p->gui->win, 105, 755, WHITE, str);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}
