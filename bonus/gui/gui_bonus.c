/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:55:28 by amorel            #+#    #+#             */
/*   Updated: 2022/12/05 17:49:04 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	clear_screen(void *mlx, void *win, void *bg)
{
	mlx_put_image_to_window(mlx, win, bg, 0, 0);
}

t_gui	*init_gui(void *mlx)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	gui->res_x = 320;
	gui->res_y = 900;
	gui->win = mlx_new_window(mlx, gui->res_x, gui->res_y, "GUI");
	gui->light_id = 0;
	gui->light_nb = 0;
	gui->bump_nb = get_file_number("ressources/bumpmaps");
	gui->texture_nb = 0;
	gui->bump_names = NULL;
	gui->texture_names = NULL;
	gui->selection = NULL;
	load_gui_images(gui, mlx);
	return (gui);
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
	else if (p->gui->selection->type == CONE)
		cone_hook(x, y, p);
	else if (p->gui->selection->type == NONE)
		clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	if (x >= 50 && x <= 270 && y >= 800 && y <= 850)
		refresh_screen(p);
	return (0);
}

int	tgui_destroy(void *mlx, t_gui *gui)
{
	int	i;

	if (!gui)
		return (0);
	i = -1;
	if (gui->imgs)
	{
		while (++i < 19)
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
