/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:24:26 by amorel            #+#    #+#             */
/*   Updated: 2022/11/14 18:05:45 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	load_props(t_gui *gui, void *mlx, int x, int y)
{
	gui->imgs[DIA]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/diameter.xpm", &x, &y);
	gui->imgs[ANG]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/angle.xpm", &x, &y);
	gui->imgs[HEI]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/height.xpm", &x, &y);
	gui->imgs[RAT]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/ratio.xpm", &x, &y);
	gui->imgs[SPH]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/sphere.xpm", &x, &y);
	gui->imgs[CON]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/cone.xpm", &x, &y);
	gui->imgs[CYL]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/cylinder.xpm", &x, &y);
	gui->imgs[PLN]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/plane.xpm", &x, &y);
	gui->imgs[LGT]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/light.xpm", &x, &y);
	gui->imgs[AMB]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/amblight.xpm", &x, &y);
	gui->imgs[TEX]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/texture.xpm", &x, &y);
	gui->imgs[BMP]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/bumpmap.xpm", &x, &y);
}

void	load_plusminus(t_gui *gui, void *mlx, int x, int y)
{
	gui->imgs[PLS]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/plus.xpm", &x, &y);
	gui->imgs[MIN]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/minus.xpm", &x, &y);
}

void	load_vector(t_gui *gui, void *mlx, int x, int y)
{
	gui->imgs[POS]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/pos.xpm", &x, &y);
	gui->imgs[DIREC]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/dir.xpm", &x, &y);
}
