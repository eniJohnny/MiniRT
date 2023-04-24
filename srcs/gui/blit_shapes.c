/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:38:02 by amorel            #+#    #+#             */
/*   Updated: 2022/11/14 16:18:27 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	blit_sphere_imgs(void *mlx, t_gui *gui)
{
	int	first;

	first = 65;
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[SPH]->image, 20, 20);
	first = print_diameter(mlx, gui, 0, first);
	first = print_position(mlx, gui, 0, first);
	first = print_rgb(mlx, gui, 0, 175);
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[REF]->image, 50, 800);
}

void	blit_cylinder_imgs(void *mlx, t_gui *gui)
{
	int	first;

	first = 65;
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[CYL]->image, 20, 20);
	first = print_diameter(mlx, gui, 0, first);
	first = print_height(mlx, gui, 0, first);
	first = print_position(mlx, gui, 0, first);
	first = print_direction(mlx, gui, 0, first);
	first = print_rgb(mlx, gui, 0, first);
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[REF]->image, 50, 800);
}

void	blit_plane_imgs(void *mlx, t_gui *gui)
{
	int	first;

	first = 65;
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[PLN]->image, 20, 20);
	first = print_position(mlx, gui, 0, first);
	first = print_direction(mlx, gui, 0, first);
	first = print_rgb(mlx, gui, 0, first);
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[REF]->image, 50, 800);
}
