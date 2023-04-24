/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:56:12 by johrober          #+#    #+#             */
/*   Updated: 2022/11/21 15:46:48 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double	**init_bumpmap_array(t_img *img)
{
	double	**bm;
	int		count;

	bm = malloc(sizeof(double *) * img->height);
	if (!bm)
		return (NULL);
	count = -1;
	while (++count < img->height)
	{
		bm[count] = malloc(sizeof(double) * img->width);
		if (!bm[count])
			break ;
	}
	if (count < img->height)
	{
		while (--count >= 0)
			free(bm[count]);
		free(bm);
		return (NULL);
	}
	return (bm);
}

static double	**bumpmap_to_double(t_img *img)
{
	double	**bm;
	int		x;
	int		y;
	int		buf_index;

	bm = init_bumpmap_array(img);
	if (!bm)
		return (NULL);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			buf_index = y * img->l_bits + x * 4;
			bm[y][x] = (255.0 - img->buf[buf_index + 1]) / 255.0;
		}
	}
	return (bm);
}

static t_bumpmap	*load_bump_map(t_program *p, char *file)
{
	t_img		*img;
	static int	index = -1;

	index++;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	p->bm[index] = malloc(sizeof(t_bumpmap));
	if (!p->bm[index])
	{
		free(img);
		return (NULL);
	}
	img->image = mlx_xpm_file_to_image(p->mlx, file, &img->width, &img->height);
	img->buf = (unsigned char *)mlx_get_data_addr(img->image, &img->p_bits, \
		&img->l_bits, &img->endian);
	p->bm[index]->img = img;
	p->bm[index]->map = bumpmap_to_double(img);
	printf("Bumpmap %s number %d loaded\n", file, index);
	return (p->bm[index]);
}

void	load_bump_map_list(t_program *p)
{
	DIR				*dir;
	struct dirent	*dent;
	char			*filepath;
	int				i;

	i = 0;
	dir = opendir("ressources/bumpmaps");
	if (!dir)
		clean_exit(p, EXIT_FAILURE, "Fatal Error\n");
	p->bm = malloc(sizeof(t_bumpmap *) * p->gui->bump_nb);
	if (!p->bm)
		clean_exit(p, EXIT_FAILURE, "Fatal Error\n");
	while (i < p->gui->bump_nb)
	{
		dent = readdir(dir);
		if (dent && ft_strlen(dent->d_name) > 4)
		{
			filepath = ft_strjoin("ressources/bumpmaps/", dent->d_name);
			load_bump_map(p, filepath);
			free(filepath);
			i++;
		}
	}
	closedir(dir);
	sort_bumpmaps(p);
}
