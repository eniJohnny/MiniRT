/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:30:47 by amorel            #+#    #+#             */
/*   Updated: 2022/11/05 15:21:56 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	change_light_pos(t_program *p, int x, unsigned char c)
{
	t_light	*light;
	double	nb;

	nb = 0.5;
	if (x >= 70 && x < 86)
		nb = -0.5;
	light = (t_light *)p->gui->selection->object;
	if (c == 'x')
		light->pos->x += nb;
	else if (c == 'y')
		light->pos->y += nb;
	else if (c == 'z')
		light->pos->z += nb;
	print_light(p, p->gui->selection);
}

void	change_light_rgb(t_program *p, int x, unsigned char c)
{
	t_light	*light;
	double	nb;

	nb = 0.05;
	if (x >= 30 && x < 46)
		nb = -0.05;
	light = (t_light *)p->gui->selection->object;
	if (c == 'r')
		light->rgb->r = fmax(fmin(light->rgb->r + nb, 1.0), 0.0);
	else if (c == 'g')
		light->rgb->g = fmax(fmin(light->rgb->g + nb, 1.0), 0.0);
	else if (c == 'b')
		light->rgb->b = fmax(fmin(light->rgb->b + nb, 1.0), 0.0);
	print_light(p, p->gui->selection);
}

void	change_light_ratio(t_program *p, int x)
{
	t_light	*light;
	double	nb;

	nb = 0.05;
	if (x >= 55 && x < 71)
		nb = -0.05;
	light = (t_light *)p->gui->selection->object;
	light->ratio = fmax(light->ratio + nb, 0);
	print_light(p, p->gui->selection);
}
