/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:13:54 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 16:50:33 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	hook_loop(t_program *p)
{
	(void)p;
	return (0);
}

int	hook_key(int keycode, t_program *p)
{
	if (keycode == 65307)
		close_win(p);
	else if (keycode == XK_w || keycode == XK_a || keycode == XK_s
		|| keycode == XK_d || keycode == XK_q || keycode == XK_e)
		move_camera(p, keycode);
	else if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Left
		|| keycode == XK_Right)
		rotate_camera(p, keycode);
	return (0);
}

int	hook_mouse(int button, int x, int y, t_program *p)
{
	t_hit	*hit;

	(void)button;
	hit = malloc(sizeof(t_hit));
	if (!hit)
		return (0);
	get_closest_hit(hit, p, p->rays[y][x]);
	if (hit->type == SPHERE)
		print_sphere(p, hit);
	else if (hit->type == CYLINDER)
		print_cylinder(p, hit);
	else if (hit->type == PLANE)
		print_plane(p, hit);
	else if (hit->type == CONE)
		print_cone(p, hit);
	return (0);
}

int	close_win(t_program *p)
{
	clean_exit(p, EXIT_SUCCESS, NULL);
	return (0);
}
