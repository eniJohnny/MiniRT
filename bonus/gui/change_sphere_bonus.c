/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:55:56 by amorel            #+#    #+#             */
/*   Updated: 2022/11/02 18:56:39 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	change_sph_diameter(t_program *p, int x)
{
	t_sphere	*sph;
	double		nb;

	nb = 0.5;
	if (x >= 105 && x < 121)
		nb = -0.5;
	sph = (t_sphere *)p->gui->selection->object;
	sph->diameter = fmax(sph->diameter + nb, 0);
	print_sphere(p, p->gui->selection);
}

void	change_sph_pos(t_program *p, int x, unsigned char c)
{
	t_sphere	*sph;
	double		nb;

	nb = 0.5;
	if (x >= 70 && x < 86)
		nb = -0.5;
	sph = (t_sphere *)p->gui->selection->object;
	if (c == 'x')
		sph->pos->x += nb;
	else if (c == 'y')
		sph->pos->y += nb;
	else if (c == 'z')
		sph->pos->z += nb;
	print_sphere(p, p->gui->selection);
}

void	change_sph_rgb(t_program *p, int x, unsigned char c)
{
	t_sphere	*sph;
	double		nb;

	nb = 0.05;
	if (x >= 30 && x < 46)
		nb = -0.05;
	sph = (t_sphere *)p->gui->selection->object;
	if (c == 'r')
		sph->rgb->r = fmax(fmin(sph->rgb->r + nb, 1.0), 0.0);
	else if (c == 'g')
		sph->rgb->g = fmax(fmin(sph->rgb->g + nb, 1.0), 0.0);
	else if (c == 'b')
		sph->rgb->b = fmax(fmin(sph->rgb->b + nb, 1.0), 0.0);
	print_sphere(p, p->gui->selection);
}
