/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:08:32 by amorel            #+#    #+#             */
/*   Updated: 2022/11/14 17:12:38 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	print_ratio(void *mlx, t_gui *gui, int x, int y)
{
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[RAT]->image, x, y);
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[MIN]->image,
		x + 55, y + 4);
	mlx_put_image_to_window(mlx, gui->win, gui->imgs[PLS]->image,
		x + 71, y + 4);
	return (y + 30);
}

int	print_angle(void *mlx, t_gui *g, int x, int y)
{
	mlx_put_image_to_window(mlx, g->win, g->imgs[ANG]->image, x, y);
	mlx_put_image_to_window(mlx, g->win, g->imgs[MIN]->image, x + 68, y + 4);
	mlx_put_image_to_window(mlx, g->win, g->imgs[PLS]->image, x + 83, y + 4);
	return (y + 30);
}

void	print_to_gui(t_program *p, double n, int x, int y)
{
	char	*str;
	int		color;

	str = NULL;
	color = (255 << 16) + (255 << 8) + 255;
	str = ft_ftoa_free(n, str);
	mlx_string_put(p->mlx, p->gui->win, x, y, color, str);
	free(str);
}
