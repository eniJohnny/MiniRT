/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:22:16 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 15:51:18 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	get_file_number(char *filepath)
{
	int				n;
	DIR				*dir;
	struct dirent	*dent;

	n = 0;
	dir = opendir(filepath);
	if (!dir)
		return (0);
	dent = readdir(dir);
	dent = readdir(dir);
	dent = readdir(dir);
	while (dent)
	{
		dent = readdir(dir);
		n++;
	}
	if (dir)
		closedir(dir);
	return (n);
}

static void	get_bump_names(t_gui *gui)
{
	DIR				*dir;
	struct dirent	*dent;
	int				i;

	i = 0;
	gui->bump_names = malloc(sizeof(char *) * (gui->bump_nb));
	if (!gui->bump_names)
		return ;
	dir = opendir("ressources/bumpmaps");
	if (!dir)
		return ;
	while (i < gui->bump_nb)
	{
		dent = readdir(dir);
		if (dent && is_valid_extension(dent->d_name, ".xpm"))
		{
			gui->bump_names[i] = malloc(sizeof(char)
					* (ft_strlen(dent->d_name) - 3));
			ft_strlcpy(gui->bump_names[i], dent->d_name,
				ft_strlen(dent->d_name) - 3);
			i++;
		}
	}
	if (dir)
		closedir(dir);
}

static void	get_texture_names(t_gui *gui)
{
	DIR				*dir;
	struct dirent	*dent;
	int				i;

	i = 0;
	gui->texture_names = malloc(sizeof(char *) * (gui->bump_nb + 1));
	dir = opendir("ressources/textures");
	if (!dir)
		return ;
	dent = readdir(dir);
	while (dent)
	{
		if (dent && is_valid_extension(dent->d_name, ".xpm"))
		{
			gui->texture_names[i] = malloc(sizeof(char)
					* (ft_strlen(dent->d_name) - 3));
			ft_strlcpy(gui->texture_names[i], dent->d_name,
				ft_strlen(dent->d_name) - 3);
			i++;
		}
		dent = readdir(dir);
	}
	closedir(dir);
	gui->texture_names[i] = NULL;
}

static void	init_gui_imgs(t_gui *gui)
{
	int	i;

	i = -1;
	get_bump_names(gui);
	get_texture_names(gui);
	gui->imgs = malloc(sizeof(t_img *) * 19);
	if (!gui->imgs)
		return ;
	while (++i < 19)
		gui->imgs[i] = malloc(sizeof(t_img));
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
