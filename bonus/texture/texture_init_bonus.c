/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:11:45 by johrober          #+#    #+#             */
/*   Updated: 2022/12/05 17:37:18 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_img	*load_texture(t_program *p, char *file)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->image = mlx_xpm_file_to_image(p->mlx, file, &img->width, &img->height);
	img->buf = (unsigned char *)mlx_get_data_addr(img->image, \
		&img->p_bits, &img->l_bits, &img->endian);
	return (img);
}

void	load_texture_list(t_program *p)
{
	DIR				*dir;
	struct dirent	*dent;
	char			*filepath;
	int				i;

	i = 0;
	p->gui->texture_nb = p->gui->bump_nb;
	dir = opendir("ressources/textures");
	p->textures = malloc(sizeof(t_img *) * p->gui->texture_nb);
	if (!dir || !p->textures)
		clean_exit(p, EXIT_FAILURE, "Fatal Error\n");
	dent = readdir(dir);
	while (dent)
	{
		if (is_valid_extension(dent->d_name, ".xpm"))
		{
			filepath = ft_strjoin("ressources/textures/", dent->d_name);
			p->textures[i] = load_texture(p, filepath);
			free(filepath);
			i++;
		}
		dent = readdir(dir);
	}
	closedir(dir);
	sort_textures(p);
}

void	free_texture_list(t_program *p)
{
	int	i;

	i = -1;
	if (!p->gui || !p->gui->texture_names)
		return ;
	while (++i < p->gui->bump_nb)
	{
		free(p->gui->texture_names[i]);
		mlx_destroy_image(p->mlx, p->textures[i]->image);
		free(p->textures[i]);
	}
	free(p->gui->texture_names);
	free(p->textures);
}
