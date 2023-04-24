/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_mapping_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:23:33 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 15:27:16 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_checkered_cone_color(t_rgb *rgb, t_hit *hit, t_cone *cne)
{
	double	xy[2];
	double	sides[2];
	int		chk_nb[2];
	double	ratio[2];

	get_projected_cone_point(hit, cne, (double *)xy);
	sides[0] = cne->height / cos(cne->angle);
	sides[1] = tan(cne->angle) * cne->height;
	ratio[1] = sides[1] / (sides[0] + sides[1]);
	ratio[0] = sides[0] / (sides[1] * M_PI);
	chk_nb[0] = fmax((double)CHK_CYL * ratio[0], 1.0);
	ratio[0] = sides[1] / fmax(sides[0], 0.5);
	chk_nb[1] = (double)chk_nb[0] * ratio[0];
	ratio[0] = (double)chk_nb[1] / (double)(chk_nb[1] + chk_nb[0]);
	xy[0] *= (double)CHK_CYL;
	if (xy[1] <= (1.0 - ratio[1]))
		xy[1] = xy[1] * (1.0 - ratio[0]) / (1.0 - ratio[1]);
	else
		xy[1] = (1.0 - ratio[0]) + (xy[1] - (1.0 - ratio[1]))
			* ratio[0] / ratio[1];
	xy[1] *= (double)(chk_nb[0] + chk_nb[1]);
	if ((int)(floor(xy[0]) + floor(xy[1])) % 2 == 0)
		to_rgb(rgb, 0.1, 0.1, 0.1);
	else
		copy_rgb(rgb, cne->rgb);
}

void	get_cone_color(t_rgb *rgb, t_program *p, t_hit *hit, t_cone *cne)
{
	if (cne->bump == -1)
		copy_rgb(rgb, cne->rgb);
	else if (cne->bump == -2)
		get_checkered_cone_color(rgb, hit, cne);
	else if (cne->bump >= 0 && cne->bump < p->gui->texture_nb)
		get_texture_color(rgb, p, hit);
	else
		copy_rgb(rgb, cne->rgb);
}
