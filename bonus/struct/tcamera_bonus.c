/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcamera_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:25:39 by johrober          #+#    #+#             */
/*   Updated: 2022/12/12 14:50:41 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_camera	*tcamera_init(void)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->pos = NULL;
	cam->dir = NULL;
	cam->x = NULL;
	cam->y = NULL;
	cam->z = NULL;
	cam->fov = 0;
	cam->height = 0;
	cam->width = 0;
	if (tcamera_allocate(cam))
	{
		tcamera_destroy(cam);
		return (NULL);
	}
	return (cam);
}

int	tcamera_allocate(t_camera *cam)
{
	cam->pos = malloc(sizeof(t_vec));
	if (!cam->pos)
		return (1);
	cam->dir = malloc(sizeof(t_vec));
	if (!cam->dir)
		return (1);
	cam->x = malloc(sizeof(t_vec));
	if (!cam->x)
		return (1);
	cam->y = malloc(sizeof(t_vec));
	if (!cam->y)
		return (1);
	cam->z = malloc(sizeof(t_vec));
	if (!cam->z)
		return (1);
	return (0);
}

void	tcamera_destroy(t_camera *cam)
{
	if (!cam)
		return ;
	if (cam->pos)
		free(cam->pos);
	if (cam->dir)
		free(cam->dir);
	if (cam->x)
		free(cam->x);
	if (cam->y)
		free(cam->y);
	if (cam->z)
		free(cam->z);
	free(cam);
}

int	lst_add_back_camera(t_program *p, char **array)
{
	if (p->camera || !check_camera(array))
		return (1);
	p->camera = tcamera_init();
	if (!p->camera)
		return (1);
	init_pos(p->camera->pos, array[1]);
	init_vector(p->camera->dir, array[2]);
	p->camera->fov = ft_atoi(array[3]);
	return (0);
}
