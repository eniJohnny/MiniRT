/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:50:09 by johrober          #+#    #+#             */
/*   Updated: 2022/11/05 14:56:41 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	render(t_program *p, t_rgb **tab)
{
	if (p->img != NULL && p->img->image != NULL)
	{
		mlx_destroy_image(p->mlx, p->img->image);
		free(p->img);
	}
	p->img = get_img(p, tab);
	mlx_put_image_to_window(p->mlx, p->win, p->img->image, 0, 0);
}

t_img	*get_img(t_program *p, t_rgb **tab)
{
	p->img = malloc(sizeof(t_img));
	if (!p->img)
		clean_exit(p, EXIT_FAILURE, "Fatal error\n");
	p->img->image = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	p->img->buf = (unsigned char *)mlx_get_data_addr(p->img->image,
			&p->img->p_bits, &p->img->l_bits, &p->img->endian);
	fill_img(p->img, tab);
	return (p->img);
}

void	fill_img(t_img *img, t_rgb **tab)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			fill_pixel(img, tab, x, y);
		}
	}
}

void	fill_pixel(t_img *img, t_rgb **tab, int x, int y)
{
	int	buf_index;

	buf_index = y * img->l_bits + x * 4;
	if (img->endian == 0)
	{
		img->buf[buf_index + 0] = tab[y][x].b * 255;
		img->buf[buf_index + 1] = tab[y][x].g * 255;
		img->buf[buf_index + 2] = tab[y][x].r * 255;
		img->buf[buf_index + 3] = 255;
	}
	else
	{
		img->buf[buf_index + 0] = 255;
		img->buf[buf_index + 1] = tab[y][x].r * 255;
		img->buf[buf_index + 2] = tab[y][x].g * 255;
		img->buf[buf_index + 3] = tab[y][x].b * 255;
	}
}
