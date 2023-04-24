/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_amb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:30:47 by amorel            #+#    #+#             */
/*   Updated: 2022/11/05 15:21:20 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	change_amb_rgb(t_program *p, int x, unsigned char c)
{
	t_amblight	*amb;
	double		nb;

	nb = 0.05;
	if (x >= 30 && x < 46)
		nb = -0.05;
	amb = (t_amblight *)p->gui->selection->object;
	if (c == 'r')
		amb->rgb->r = fmax(fmin(amb->rgb->r + nb, 1.0), 0.0);
	else if (c == 'g')
		amb->rgb->g = fmax(fmin(amb->rgb->g + nb, 1.0), 0.0);
	else if (c == 'b')
		amb->rgb->b = fmax(fmin(amb->rgb->b + nb, 1.0), 0.0);
	print_amblight(p, p->gui->selection);
}

void	change_amb_ratio(t_program *p, int x)
{
	t_amblight	*amb;
	double		nb;

	nb = 0.05;
	if (x >= 55 && x < 71)
		nb = -0.05;
	amb = (t_amblight *)p->gui->selection->object;
	amb->ratio = fmax(amb->ratio + nb, 0);
	print_amblight(p, p->gui->selection);
}
