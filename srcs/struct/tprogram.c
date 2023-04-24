/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tprogram.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:36:25 by johrober          #+#    #+#             */
/*   Updated: 2022/11/30 16:14:35 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	p->img = NULL;
	p->res_x = WIDTH;
	p->res_y = HEIGHT;
	p->rays = NULL;
	return (p);
}

void	tprogram_load(t_program *p)
{
	int			i;

	i = -1;
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, p->res_x, p->res_y, WINDOW_NAME);
	p->gui = init_gui(p->mlx);
	p->map = malloc(HEIGHT * sizeof(t_rgb));
	if (!p->map)
		clean_exit(p, EXIT_FAILURE, "Fatal error\n");
	while (++i < HEIGHT)
		p->map[i] = malloc(sizeof(t_rgb) * WIDTH);
	mlx_hook(p->win, 17, 0L, close_win, p);
	mlx_loop_hook(p->mlx, hook_loop, p);
	mlx_key_hook(p->win, hook_key, p);
	mlx_mouse_hook(p->win, hook_mouse, p);
	mlx_hook(p->gui->win, 17, 0L, close_win, p);
	mlx_key_hook(p->gui->win, gui_hook_key, p);
	mlx_mouse_hook(p->gui->win, gui_hook_mouse, p);
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
				if (rays[i][j]->hit_list)
					free(rays[i][j]->hit_list);
				free(rays[i][j]);
				rays[i][j] = NULL;
			}
		}
		if (rays[i])
			free(rays[i]);
	}
	free(rays);
	rays = NULL;
}

int	tprogram_destroy(t_program *p)
{
	int	i;

	tamblight_destroy(p->amblight);
	tlight_destroy(p->light);
	tplane_destroy_all(p->plane);
	tsphere_destroy_all(p->sphere);
	tcamera_destroy(p->camera);
	tcylinder_destroy_all(p->cylinder);
	i = -1;
	while (++i < HEIGHT)
		free(p->map[i]);
	free(p->map);
	if (!p || !p->rays)
		return (1);
	free_rays(p->rays);
	return (0);
}
