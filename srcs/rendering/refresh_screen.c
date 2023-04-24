/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:36:19 by amorel            #+#    #+#             */
/*   Updated: 2022/11/22 13:58:43 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_camera(t_program *p, int key)
{
	if (key == XK_w)
		vector_sum(p->camera->pos, p->camera->pos, p->camera->z);
	else if (key == XK_s)
		vector_sub(p->camera->pos, p->camera->pos, p->camera->z);
	else if (key == XK_a)
		vector_sum(p->camera->pos, p->camera->pos, p->camera->x);
	else if (key == XK_d)
		vector_sub(p->camera->pos, p->camera->pos, p->camera->x);
	else if (key == XK_e)
		vector_sum(p->camera->pos, p->camera->pos, p->camera->y);
	else if (key == XK_q)
		vector_sub(p->camera->pos, p->camera->pos, p->camera->y);
	render_scene(p);
}

void	rotate_camera(t_program *p, int key)
{
	t_quat	*qt;
	t_vec	y_axis;

	qt = NULL;
	to_vector(&y_axis, 0, 1, 0);
	if (key == XK_Up)
		qt = get_allocated_quaternion(p->camera->x, CAMR * DEGREE_TO_RADIAN);
	else if (key == XK_Down)
		qt = get_allocated_quaternion(p->camera->x, -CAMR * DEGREE_TO_RADIAN);
	else if (key == XK_Left)
		qt = get_allocated_quaternion(&y_axis, -CAMR * DEGREE_TO_RADIAN);
	else if (key == XK_Right)
		qt = get_allocated_quaternion(&y_axis, CAMR * DEGREE_TO_RADIAN);
	if (!qt)
		return ;
	apply_rotation(p->camera->dir, qt);
	free(qt);
	render_scene(p);
}

void	refresh_screen(t_program *p)
{
	free(p->gui->selection);
	p->gui->selection = NULL;
	render_scene(p);
	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
}
