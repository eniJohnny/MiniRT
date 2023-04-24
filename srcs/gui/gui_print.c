/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:41:59 by amorel            #+#    #+#             */
/*   Updated: 2022/11/18 17:38:15 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_program *p, t_hit *hit)
{
	t_sphere	*sph;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_sphere_imgs(p->mlx, p->gui);
	sph = (t_sphere *)(hit->object);
	print_to_gui(p, sph->diameter, 151, 81);
	print_to_gui(p, sph->pos->x, 116, 110);
	print_to_gui(p, sph->pos->y, 116, 134);
	print_to_gui(p, sph->pos->z, 116, 158);
	print_to_gui(p, sph->rgb->r, 76, 190);
	print_to_gui(p, sph->rgb->g, 76, 214);
	print_to_gui(p, sph->rgb->b, 76, 238);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}

void	print_cylinder(t_program *p, t_hit *hit)
{
	t_cylinder	*cyl;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_cylinder_imgs(p->mlx, p->gui);
	cyl = (t_cylinder *)(hit->object);
	print_to_gui(p, cyl->diameter, 151, 81);
	print_to_gui(p, cyl->height, 122, 111);
	print_to_gui(p, cyl->pos->x, 116, 140);
	print_to_gui(p, cyl->pos->y, 116, 164);
	print_to_gui(p, cyl->pos->z, 116, 188);
	print_to_gui(p, cyl->dir->x, 116, 233);
	print_to_gui(p, cyl->dir->y, 116, 257);
	print_to_gui(p, cyl->dir->z, 116, 281);
	print_to_gui(p, cyl->rgb->r, 76, 326);
	print_to_gui(p, cyl->rgb->g, 76, 350);
	print_to_gui(p, cyl->rgb->b, 76, 374);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}

void	print_plane(t_program *p, t_hit *hit)
{
	t_plane	*pln;

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
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}

void	print_amblight(t_program *p, t_hit *hit)
{
	t_amblight	*amb;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_amblight_imgs(p->mlx, p->gui);
	amb = (t_amblight *)(hit->object);
	print_to_gui(p, amb->ratio, 100, 81);
	print_to_gui(p, amb->rgb->r, 76, 111);
	print_to_gui(p, amb->rgb->g, 76, 135);
	print_to_gui(p, amb->rgb->b, 76, 159);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}

void	print_light(t_program *p, t_hit *hit)
{
	t_light	*light;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_light_imgs(p->mlx, p->gui);
	light = (t_light *)(hit->object);
	print_to_gui(p, light->ratio, 100, 81);
	print_to_gui(p, light->pos->x, 116, 111);
	print_to_gui(p, light->pos->y, 116, 135);
	print_to_gui(p, light->pos->z, 116, 159);
	print_to_gui(p, light->rgb->r, 76, 204);
	print_to_gui(p, light->rgb->g, 76, 228);
	print_to_gui(p, light->rgb->b, 76, 252);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
}
