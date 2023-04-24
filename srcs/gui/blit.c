/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:20:18 by amorel            #+#    #+#             */
/*   Updated: 2022/11/10 19:38:28 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	blit_amblight_imgs(void *mlx, t_gui *gui)
{
	int	first;

	first = 65;
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[AMB]->image, 20, 20);
	first = print_ratio(mlx, gui, 0, first);
	first = print_rgb(mlx, gui, 0, first);
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[REF]->image, 50, 800);
}

void	blit_light_imgs(void *mlx, t_gui *gui)
{
	int	first;

	first = 65;
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[LGT]->image, 20, 20);
	first = print_ratio(mlx, gui, 0, first);
	first = print_position(mlx, gui, 0, first);
	first = print_rgb(mlx, gui, 0, first);
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[REF]->image, 50, 800);
}
