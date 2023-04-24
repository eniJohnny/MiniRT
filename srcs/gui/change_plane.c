/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:55:56 by amorel            #+#    #+#             */
/*   Updated: 2022/11/05 15:22:11 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_pln_pos(t_program *p, int x, unsigned char c)
{
	t_plane	*pln;
	double	nb;

	nb = 0.5;
	if (x >= 70 && x < 86)
		nb = -0.5;
	pln = (t_plane *)p->gui->selection->object;
	if (c == 'x')
		pln->pos->x += nb;
	else if (c == 'y')
		pln->pos->y += nb;
	else if (c == 'z')
		pln->pos->z += nb;
	print_plane(p, p->gui->selection);
}

void	change_pln_dir(t_program *p, int x, unsigned char c)
{
	t_plane	*pln;
	double	nb;

	nb = 0.05;
	if (x >= 70 && x < 86)
		nb = -0.05;
	pln = (t_plane *)p->gui->selection->object;
	if (c == 'x')
		pln->dir->x += nb;
	else if (c == 'y')
		pln->dir->y += nb;
	else if (c == 'z')
		pln->dir->z += nb;
	pln->dir = vector_normalize(pln->dir);
	print_plane(p, p->gui->selection);
}

void	change_pln_rgb(t_program *p, int x, unsigned char c)
{
	t_plane	*pln;
	double	nb;

	nb = 0.05;
	if (x >= 30 && x < 46)
		nb = -0.05;
	pln = (t_plane *)p->gui->selection->object;
	if (c == 'r')
		pln->rgb->r = fmax(fmin(pln->rgb->r + nb, 1.0), 0.0);
	else if (c == 'g')
		pln->rgb->g = fmax(fmin(pln->rgb->g + nb, 1.0), 0.0);
	else if (c == 'b')
		pln->rgb->b = fmax(fmin(pln->rgb->b + nb, 1.0), 0.0);
	print_plane(p, p->gui->selection);
}
