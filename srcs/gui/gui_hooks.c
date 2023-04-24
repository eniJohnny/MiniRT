/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:23:58 by amorel            #+#    #+#             */
/*   Updated: 2022/11/17 19:35:54 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_hook(int x, int y, t_program *p)
{
	if (x >= 105 && x < 137 && y >= 69 && y < 85)
		change_sph_diameter(p, x);
	else if (x >= 70 && x <= 102 && y >= 99 && y <= 115)
		change_sph_pos(p, x, 'x');
	else if (x >= 70 && x <= 102 && y >= 123 && y <= 139)
		change_sph_pos(p, x, 'y');
	else if (x >= 70 && x <= 102 && y >= 147 && y <= 163)
		change_sph_pos(p, x, 'z');
	else if (x >= 30 && x <= 62 && y >= 177 && y <= 193)
		change_sph_rgb(p, x, 'r');
	else if (x >= 30 && x <= 62 && y >= 201 && y <= 217)
		change_sph_rgb(p, x, 'g');
	else if (x >= 30 && x <= 62 && y >= 225 && y <= 241)
		change_sph_rgb(p, x, 'b');
}

void	cylinder_hook(int x, int y, t_program *p)
{
	if (x >= 105 && x < 137 && y >= 69 && y < 85)
		change_cyl_diameter(p, x);
	else if (x >= 80 && x < 122 && y >= 99 && y < 115)
		change_cyl_height(p, x);
	else if (x >= 70 && x <= 102 && y >= 128 && y <= 144)
		change_cyl_pos(p, x, 'x');
	else if (x >= 70 && x <= 102 && y >= 152 && y <= 167)
		change_cyl_pos(p, x, 'y');
	else if (x >= 70 && x <= 102 && y >= 176 && y <= 192)
		change_cyl_pos(p, x, 'z');
	else if (x >= 70 && x <= 102 && y >= 221 && y <= 237)
		change_cyl_dir(p, x, 'x');
	else if (x >= 70 && x <= 102 && y >= 245 && y <= 261)
		change_cyl_dir(p, x, 'y');
	else if (x >= 70 && x <= 102 && y >= 269 && y <= 285)
		change_cyl_dir(p, x, 'z');
	else if (x >= 30 && x <= 62 && y >= 304 && y <= 330)
		change_cyl_rgb(p, x, 'r');
	else if (x >= 30 && x <= 62 && y >= 338 && y <= 354)
		change_cyl_rgb(p, x, 'g');
	else if (x >= 30 && x <= 62 && y >= 362 && y <= 378)
		change_cyl_rgb(p, x, 'b');
}

void	plane_hook(int x, int y, t_program *p)
{
	if (x >= 70 && x <= 102 && y >= 69 && y <= 85)
		change_pln_pos(p, x, 'x');
	else if (x >= 70 && x <= 102 && y >= 93 && y <= 109)
		change_pln_pos(p, x, 'y');
	else if (x >= 70 && x <= 102 && y >= 117 && y <= 133)
		change_pln_pos(p, x, 'z');
	else if (x >= 70 && x <= 102 && y >= 162 && y <= 178)
		change_pln_dir(p, x, 'x');
	else if (x >= 70 && x <= 102 && y >= 186 && y <= 202)
		change_pln_dir(p, x, 'y');
	else if (x >= 70 && x <= 102 && y >= 210 && y <= 226)
		change_pln_dir(p, x, 'z');
	else if (x >= 30 && x <= 62 && y >= 255 && y <= 271)
		change_pln_rgb(p, x, 'r');
	else if (x >= 30 && x <= 62 && y >= 279 && y <= 295)
		change_pln_rgb(p, x, 'g');
	else if (x >= 30 && x <= 62 && y >= 303 && y <= 319)
		change_pln_rgb(p, x, 'b');
}

void	amblight_hook(int x, int y, t_program *p)
{
	if (x >= 55 && x <= 87 && y >= 69 && y <= 85)
		change_amb_ratio(p, x);
	else if (x >= 30 && x <= 62 && y >= 99 && y <= 115)
		change_amb_rgb(p, x, 'r');
	else if (x >= 30 && x <= 62 && y >= 123 && y <= 139)
		change_amb_rgb(p, x, 'g');
	else if (x >= 30 && x <= 62 && y >= 147 && y <= 162)
		change_amb_rgb(p, x, 'b');
}

void	light_hook(int x, int y, t_program *p)
{
	if (x >= 55 && x <= 87 && y >= 69 && y <= 85)
		change_light_ratio(p, x);
	else if (x >= 70 && x <= 102 && y >= 98 && y <= 114)
		change_light_pos(p, x, 'x');
	else if (x >= 70 && x <= 102 && y >= 122 && y <= 137)
		change_light_pos(p, x, 'y');
	else if (x >= 70 && x <= 102 && y >= 146 && y <= 168)
		change_light_pos(p, x, 'z');
	else if (x >= 30 && x <= 62 && y >= 191 && y <= 207)
		change_light_rgb(p, x, 'r');
	else if (x >= 30 && x <= 62 && y >= 215 && y <= 230)
		change_light_rgb(p, x, 'g');
	else if (x >= 30 && x <= 62 && y >= 239 && y <= 255)
		change_light_rgb(p, x, 'b');
}
