/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:01:00 by johrober          #+#    #+#             */
/*   Updated: 2022/11/12 13:47:42 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_corner_vectors(t_vec *corners, t_camera *cam)
{
	t_quat	to_edges[4];
	double	fov_rad_x;
	double	fov_rad_y;

	fov_rad_x = (double)cam->fov * DEGREE_TO_RADIAN / 2.0;
	fov_rad_y = fov_rad_x * (double)HEIGHT / (double)WIDTH;
	get_quaternion(&(to_edges[0]), cam->x, fov_rad_y);
	get_quaternion(&(to_edges[1]), cam->x, -fov_rad_y);
	get_quaternion(&(to_edges[2]), cam->y, fov_rad_x);
	get_quaternion(&(to_edges[3]), cam->y, -fov_rad_x);
	vector_copy(&(corners[0]), cam->dir);
	apply_rotation(&(corners[0]), &(to_edges[0]));
	vector_copy(&(corners[1]), &(corners[0]));
	apply_rotation(&(corners[0]), &(to_edges[2]));
	apply_rotation(&(corners[1]), &(to_edges[3]));
	vector_copy(&(corners[2]), cam->dir);
	apply_rotation(&(corners[2]), &(to_edges[1]));
	apply_rotation(&(corners[2]), &(to_edges[2]));
}

void	get_delta(t_vec *dx, t_vec *dy, t_vec *corners)
{
	vector_sub(dx, &(corners[1]), &(corners[0]));
	vector_sub(dy, &(corners[2]), &(corners[0]));
	vector_multiplication(1.0 / (float)(WIDTH - 1), dx);
	vector_multiplication(1.0 / (float)(HEIGHT - 1), dy);
}
