/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tplane.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:17:10 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 18:02:23 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*tplane_init(void)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->next = NULL;
	plane->dir = NULL;
	plane->pos = NULL;
	plane->rgb = NULL;
	if (tplane_allocate(plane))
	{
		tplane_destroy(plane);
		return (NULL);
	}
	return (plane);
}

int	tplane_allocate(t_plane *pln)
{
	pln->dir = malloc(sizeof(t_vec));
	if (!pln->dir)
		return (1);
	pln->pos = malloc(sizeof(t_vec));
	if (!pln->pos)
		return (1);
	pln->rgb = malloc(sizeof(t_rgb));
	if (!pln->rgb)
		return (1);
	return (0);
}

void	tplane_destroy(t_plane *pln)
{
	if (!pln)
		return ;
	if (pln->dir)
		free(pln->dir);
	if (pln->pos)
		free(pln->pos);
	if (pln->rgb)
		free(pln->rgb);
	free(pln);
}

void	tplane_destroy_all(t_plane *pln)
{
	t_plane	*tmp;

	if (!pln)
		return ;
	while (pln->next)
	{
		tmp = pln->next;
		if (pln->dir)
			free(pln->dir);
		if (pln->pos)
			free(pln->pos);
		if (pln->rgb)
			free(pln->rgb);
		free(pln);
		pln = tmp;
	}
	if (pln->dir)
		free(pln->dir);
	if (pln->pos)
		free(pln->pos);
	if (pln->rgb)
		free(pln->rgb);
	free(pln);
}

int	lst_add_back_plane(t_program *p, char **array)
{
	t_plane	*plane;
	t_plane	*copy;

	if (!check_plane(array))
		return (EXIT_FAILURE);
	plane = tplane_init();
	if (!plane)
		return (EXIT_FAILURE);
	copy = p->plane;
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		copy->next = plane;
	}
	else
		p->plane = plane;
	if (init_pos(plane->pos, array[1]))
		return (EXIT_FAILURE);
	if (init_vector(plane->dir, array[2]))
		return (EXIT_FAILURE);
	if (init_rgb(plane->rgb, array[3]))
		return (EXIT_FAILURE);
	plane->next = NULL;
	return (0);
}
