/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_and_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:50:34 by amorel            #+#    #+#             */
/*   Updated: 2022/11/30 17:59:19 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	increment_and_print(t_program *p, int *bump)
{
	if (p->gui->selection->type == SPHERE)
		bump = &((t_sphere *)p->gui->selection->object)->bump;
	else if (p->gui->selection->type == CYLINDER)
		bump = &((t_cylinder *)p->gui->selection->object)->bump;
	else if (p->gui->selection->type == PLANE)
		bump = &((t_plane *)p->gui->selection->object)->bump;
	else if (p->gui->selection->type == CONE)
		bump = &((t_cone *)p->gui->selection->object)->bump;
	(*bump)++;
	if (*bump >= p->gui->bump_nb)
		*bump = -2;
	if (p->gui->selection->type == SPHERE)
		print_sphere(p, p->gui->selection);
	else if (p->gui->selection->type == CYLINDER)
		print_cylinder(p, p->gui->selection);
	else if (p->gui->selection->type == PLANE)
		print_plane(p, p->gui->selection);
	else if (p->gui->selection->type == CONE)
		print_cone(p, p->gui->selection);
}
