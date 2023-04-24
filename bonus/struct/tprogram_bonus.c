/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tprogram_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:36:25 by johrober          #+#    #+#             */
/*   Updated: 2022/12/05 18:01:10 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	init_rays(t_program *p)
{
	int	x;
	int	y;

	p->rays = (t_ray ***)ft_tab_init(2, HEIGHT, WIDTH);
	if (!p->rays)
		clean_exit(p, EXIT_FAILURE, "Fatal error\n");
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			p->rays[y][x] = malloc(sizeof(t_ray));
			if (!p->rays[y][x])
				clean_exit(p, EXIT_FAILURE, "Fatal error\n");
			p->rays[y][x]->dir = malloc(sizeof(t_vec));
			if (!p->rays[y][x]->dir)
				clean_exit(p, EXIT_FAILURE, "Fatal error\n");
		}
	}
}

t_program	*tprogram_init(void)
{
	t_program	*p;

	p = malloc(sizeof(t_program));
	if (!p)
		return (NULL);
	p->amblight = NULL;
	p->camera = NULL;
	p->light = NULL;
	p->sphere = NULL;
	p->plane = NULL;
	p->cylinder = NULL;
	p->cone = NULL;
	p->img = NULL;
	init_rays(p);
	return (p);
}

void	tprogram_load(t_program *p)
{
	int			i;

	i = -1;
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	p->gui = NULL;
	if (get_file_number("ressources/textures")
		>= get_file_number("ressources/bumpmaps"))
	{
		p->gui = init_gui(p->mlx);
		load_bump_map_list(p);
		load_texture_list(p);
		mlx_hook(p->gui->win, 17, 0L, close_win, p);
		mlx_key_hook(p->gui->win, gui_hook_key, p);
		mlx_mouse_hook(p->gui->win, gui_hook_mouse, p);
	}
	p->map = malloc(HEIGHT * sizeof(t_rgb *));
	if (!p->map)
		return ;
	while (++i < HEIGHT)
		p->map[i] = malloc(sizeof(t_rgb) * WIDTH);
	mlx_hook(p->win, 17, 0L, close_win, p);
	mlx_loop_hook(p->mlx, hook_loop, p);
	mlx_key_hook(p->win, hook_key, p);
	mlx_mouse_hook(p->win, hook_mouse, p);
}

void	free_rays(t_ray ***rays)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (rays[i][j])
			{
				if (rays[i][j]->dir)
					free(rays[i][j]->dir);
				free(rays[i][j]);
				rays[i][j] = NULL;
			}
		}
		free(rays[i]);
	}
	free(rays);
	rays = NULL;
}

int	tprogram_destroy(t_program *p)
{
	int	i;

	if (!p)
		return (1);
	if (p->gui)
		free_bumpmap_list(p);
	if (p->gui)
		free_texture_list(p);
	tcamera_destroy(p->camera);
	tamblight_destroy(p->amblight);
	tlight_destroy_all(p->light);
	tplane_destroy_all(p->plane);
	tsphere_destroy_all(p->sphere);
	tcylinder_destroy_all(p->cylinder);
	tcone_destroy_all(p->cone);
	i = -1;
	if (p->map)
	{
		while (++i < HEIGHT)
			free(p->map[i]);
		free(p->map);
	}
	if (p->rays)
		free_rays(p->rays);
	return (0);
}
