/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:01:49 by amorel            #+#    #+#             */
/*   Updated: 2022/11/08 18:39:32 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_diameter(void *mlx, t_gui *g, int x, int y)
{
	mlx_put_image_to_window(mlx, g->win, g->imgs[DIA]->image, x, y);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 105, y + 4);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 121, y + 4);
	return (y + 30);
}

int	print_height(void *mlx, t_gui *g, int x, int y)
{
	mlx_put_image_to_window(mlx, g->win, g->imgs[HEI]->image, x, y);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 80, y + 4);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 96, y + 4);
	return (y + 30);
}

int	print_position(void *mlx, t_gui *g, int x, int y)
{
	mlx_put_image_to_window(mlx, g->win, g->imgs[POS]->image, x, y);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 70, y + 3);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 86, y + 3);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 70, y + 27);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 86, y + 27);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 70, y + 51);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 86, y + 51);
	return (y + 93);
}

int	print_direction(void *mlx, t_gui *g, int x, int y)
{
	mlx_put_image_to_window(mlx, g->win, g->imgs[DIREC]->image, x, y);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 70, y + 3);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 86, y + 3);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 70, y + 27);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 86, y + 27);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 70, y + 51);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 86, y + 51);
	return (y + 93);
}

int	print_rgb(void *mlx, t_gui *g, int x, int y)
{
	mlx_put_image_to_window(mlx, g->win, g->imgs[RGB]->image, x, y);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 30, y + 3);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 46, y + 3);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 30, y + 27);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 46, y + 27);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 30, y + 51);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 46, y + 51);
	return (y + 93);
}
