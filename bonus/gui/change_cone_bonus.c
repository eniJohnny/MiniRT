/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cone_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:55:56 by amorel            #+#    #+#             */
/*   Updated: 2022/12/01 18:53:31 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	change_cone_angle(t_program *p, int x)
{
	t_cone	*con;
	double	nb;

	nb = 0.1;
	if (x >= 68 && x < 84)
		nb = -0.1;
	con = (t_cone *)p->gui->selection->object;
	con->angle = fmax(con->angle + nb, 0.1);
	con->angle = fmin(con->angle, M_PI / 2 - 0.1);
	print_cone(p, p->gui->selection);
}

void	change_cone_height(t_program *p, int x)
{
	t_cone	*con;
	double	nb;

	nb = 0.5;
	if (x >= 80 && x < 96)
		nb = -0.5;
	con = (t_cone *)p->gui->selection->object;
	con->height = fmax(con->height + nb, 0);
	print_cone(p, p->gui->selection);
}

void	change_cone_pos(t_program *p, int x, unsigned char c)
{
	t_cone	*con;
	double	nb;

	nb = 0.5;
	if (x >= 70 && x < 86)
		nb = -0.5;
	con = (t_cone *)p->gui->selection->object;
	if (c == 'x')
		con->pos->x += nb;
	else if (c == 'y')
		con->pos->y += nb;
	else if (c == 'z')
		con->pos->z += nb;
	print_cone(p, p->gui->selection);
}

void	change_cone_dir(t_program *p, int x, unsigned char c)
{
	t_cone	*con;
	double	nb;

	nb = 0.05;
	if (x >= 70 && x < 86)
		nb = -0.05;
	con = (t_cone *)p->gui->selection->object;
	if (c == 'x')
		con->dir->x += nb;
	else if (c == 'y')
		con->dir->y += nb;
	else if (c == 'z')
		con->dir->z += nb;
	con->dir = vector_normalize(con->dir);
	print_cone(p, p->gui->selection);
}

void	change_cone_rgb(t_program *p, int x, unsigned char c)
{
	t_cone	*con;
	double	nb;

	nb = 0.05;
	if (x >= 30 && x < 46)
		nb = -0.05;
	con = (t_cone *)p->gui->selection->object;
	if (c == 'r')
		con->rgb->r = fmax(fmin(con->rgb->r + nb, 1.0), 0.0);
	else if (c == 'g')
		con->rgb->g = fmax(fmin(con->rgb->g + nb, 1.0), 0.0);
	else if (c == 'b')
		con->rgb->b = fmax(fmin(con->rgb->b + nb, 1.0), 0.0);
	print_cone(p, p->gui->selection);
}
