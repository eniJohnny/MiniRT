/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:55:56 by amorel            #+#    #+#             */
/*   Updated: 2022/11/03 02:38:12 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	change_cyl_diameter(t_program *p, int x)
{
	t_cylinder	*cyl;
	double		nb;

	nb = 0.5;
	if (x >= 105 && x < 121)
		nb = -0.5;
	cyl = (t_cylinder *)p->gui->selection->object;
	cyl->diameter = fmax(cyl->diameter + nb, 0);
	print_cylinder(p, p->gui->selection);
}

void	change_cyl_height(t_program *p, int x)
{
	t_cylinder	*cyl;
	double		nb;

	nb = 0.5;
	if (x >= 80 && x < 96)
		nb = -0.5;
	cyl = (t_cylinder *)p->gui->selection->object;
	cyl->height = fmax(cyl->height + nb, 0);
	print_cylinder(p, p->gui->selection);
}

void	change_cyl_pos(t_program *p, int x, unsigned char c)
{
	t_cylinder	*cyl;
	double		nb;

	nb = 0.5;
	if (x >= 70 && x < 86)
		nb = -0.5;
	cyl = (t_cylinder *)p->gui->selection->object;
	if (c == 'x')
		cyl->pos->x += nb;
	else if (c == 'y')
		cyl->pos->y += nb;
	else if (c == 'z')
		cyl->pos->z += nb;
	print_cylinder(p, p->gui->selection);
}

void	change_cyl_dir(t_program *p, int x, unsigned char c)
{
	t_cylinder	*cyl;
	double		nb;

	nb = 0.05;
	if (x >= 70 && x < 86)
		nb = -0.05;
	cyl = (t_cylinder *)p->gui->selection->object;
	if (c == 'x')
		cyl->dir->x += nb;
	else if (c == 'y')
		cyl->dir->y += nb;
	else if (c == 'z')
		cyl->dir->z += nb;
	cyl->dir = vector_normalize(cyl->dir);
	print_cylinder(p, p->gui->selection);
}

void	change_cyl_rgb(t_program *p, int x, unsigned char c)
{
	t_cylinder	*cyl;
	double		nb;

	nb = 0.05;
	if (x >= 30 && x < 46)
		nb = -0.05;
	cyl = (t_cylinder *)p->gui->selection->object;
	if (c == 'r')
		cyl->rgb->r = fmax(fmin(cyl->rgb->r + nb, 1.0), 0.0);
	else if (c == 'g')
		cyl->rgb->g = fmax(fmin(cyl->rgb->g + nb, 1.0), 0.0);
	else if (c == 'b')
		cyl->rgb->b = fmax(fmin(cyl->rgb->b + nb, 1.0), 0.0);
	print_cylinder(p, p->gui->selection);
}
