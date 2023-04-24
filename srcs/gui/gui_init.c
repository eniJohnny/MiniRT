/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:22:16 by amorel            #+#    #+#             */
/*   Updated: 2022/11/14 17:27:47 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_gui_imgs(t_gui *gui)
{
	int	i;

	i = -1;
	gui->imgs = malloc(sizeof(t_img *) * 15);
	if (!gui->imgs)
		return ;
	while (++i < 15)
		gui->imgs[i] = malloc(sizeof(t_img));
}

static void	load_props(t_gui *gui, void *mlx, int x, int y)
{
	gui->imgs[DIA]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/diameter.xpm", &x, &y);
	gui->imgs[HEI]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/height.xpm", &x, &y);
	gui->imgs[RAT]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/ratio.xpm", &x, &y);
	gui->imgs[SPH]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/sphere.xpm", &x, &y);
	gui->imgs[CYL]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/cylinder.xpm", &x, &y);
	gui->imgs[PLN]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/plane.xpm", &x, &y);
	gui->imgs[LGT]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/light.xpm", &x, &y);
	gui->imgs[AMB]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/amblight.xpm", &x, &y);
}

static void	load_plusminus(t_gui *gui, void *mlx, int x, int y)
{
	gui->imgs[PLS]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/plus.xpm", &x, &y);
	gui->imgs[MIN]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/minus.xpm", &x, &y);
}

static void	load_vector(t_gui *gui, void *mlx, int x, int y)
{
	gui->imgs[POS]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/pos.xpm", &x, &y);
	gui->imgs[DIREC]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/dir.xpm", &x, &y);
}

void	load_gui_images(t_gui *gui, void *mlx)
{
	int	y;
	int	x;

	init_gui_imgs(gui);
	if (!gui->imgs)
		return ;
	x = 320;
	y = 900;
	gui->imgs[BG]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/base.xpm", &x, &y);
	load_plusminus(gui, mlx, 16, 16);
	load_props(gui, mlx, 105, 20);
	load_vector(gui, mlx, 60, 70);
	x = 60;
	y = 70;
	gui->imgs[RGB]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/rgb.xpm", &x, &y);
	x = 220;
	y = 50;
	gui->imgs[REF]->image \
		= mlx_xpm_file_to_image(mlx, "ressources/images/refresh.xpm", &x, &y);
	printf("images loaded\n");
}
