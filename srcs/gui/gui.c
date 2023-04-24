/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:55:28 by amorel            #+#    #+#             */
/*   Updated: 2022/11/22 14:03:04 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_gui	*init_gui(void *mlx)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	gui->res_x = 320;
	gui->res_y = 900;
	gui->win = mlx_new_window(mlx, gui->res_x, gui->res_y, "GUI");
	gui->selection = NULL;
	load_gui_images(gui, mlx);
	return (gui);
}

void	clear_screen(void *mlx, void *win, void *bg)
{
	mlx_put_image_to_window(mlx, win, bg, 0, 0);
}

int	gui_hook_mouse(int button, int x, int y, t_program *p)
{
	(void)button;
	if (!p->gui->selection)
		return (0);
	if (p->gui->selection->type == SPHERE)
		sphere_hook(x, y, p);
	else if (p->gui->selection->type == CYLINDER)
		cylinder_hook(x, y, p);
	else if (p->gui->selection->type == PLANE)
		plane_hook(x, y, p);
	else if (p->gui->selection->type == LIGHT)
		light_hook(x, y, p);
	else if (p->gui->selection->type == AMBLIGHT)
		amblight_hook(x, y, p);
	else if (p->gui->selection->type == NONE)
		clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	if (x >= 50 && x <= 270 && y >= 800 && y <= 850)
		refresh_screen(p);
	return (0);
}

int	gui_hook_key(int keycode, t_program *p)
{
	t_hit	*hit;

	if (keycode == XK_l)
	{
		hit = malloc(sizeof(t_hit));
		if (!hit)
			return (1);
		hit->type = LIGHT;
		hit->object = (t_light *)p->light;
		print_light(p, hit);
	}
	else if (keycode == XK_o)
	{
		hit = malloc(sizeof(t_hit));
		if (!hit)
			return (1);
		hit->type = AMBLIGHT;
		hit->object = (t_amblight *)p->amblight;
		print_amblight(p, hit);
	}
	return (0);
}

int	tgui_destroy(void *mlx, t_gui *gui)
{
	int	i;

	i = -1;
	if (gui->imgs)
	{
		while (++i < 15)
		{
			mlx_destroy_image(mlx, gui->imgs[i]->image);
			free(gui->imgs[i]);
		}
		free(gui->imgs);
	}
	if (gui->selection)
		free (gui->selection);
	if (gui->win)
		mlx_destroy_window(mlx, gui->win);
	free(gui);
	return (0);
}
