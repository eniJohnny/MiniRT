/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcylinder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:18:18 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 18:03:28 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*tcylinder_init(void)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->next = NULL;
	cylinder->dir = NULL;
	cylinder->pos = NULL;
	cylinder->rgb = NULL;
	cylinder->diameter = 0;
	cylinder->height = 0;
	if (tcylinder_allocate(cylinder))
	{
		tcylinder_destroy(cylinder);
		return (NULL);
	}
	return (cylinder);
}

int	tcylinder_allocate(t_cylinder *cyl)
{
	cyl->dir = malloc(sizeof(t_vec));
	if (!cyl->dir)
		return (1);
	cyl->pos = malloc(sizeof(t_vec));
	if (!cyl->pos)
		return (1);
	cyl->rgb = malloc(sizeof(t_rgb));
	if (!cyl->rgb)
		return (1);
	return (0);
}

void	tcylinder_destroy(t_cylinder *cyl)
{
	if (!cyl)
		return ;
	if (cyl->dir)
		free(cyl->dir);
	if (cyl->pos)
		free(cyl->pos);
	if (cyl->rgb)
		free(cyl->rgb);
	free(cyl);
}

void	tcylinder_destroy_all(t_cylinder *cyl)
{
	t_cylinder	*tmp;

	if (!cyl)
		return ;
	while (cyl->next)
	{
		tmp = cyl->next;
		if (cyl->dir)
			free(cyl->dir);
		if (cyl->pos)
			free(cyl->pos);
		if (cyl->rgb)
			free(cyl->rgb);
		free(cyl);
		cyl = tmp;
	}
	if (cyl->dir)
		free(cyl->dir);
	if (cyl->pos)
		free(cyl->pos);
	if (cyl->rgb)
		free(cyl->rgb);
	free(cyl);
}

int	lst_add_back_cylinder(t_program *p, char **array)
{
	t_cylinder	*cylinder;
	t_cylinder	*copy;

	cylinder = tcylinder_init();
	if (!cylinder)
		return (EXIT_FAILURE);
	copy = p->cylinder;
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		copy->next = cylinder;
	}
	else
		p->cylinder = cylinder;
	if (!check_cylinder(array) || init_pos(cylinder->pos, array[1]))
		return (EXIT_FAILURE);
	if (init_vector(cylinder->dir, array[2]))
		return (EXIT_FAILURE);
	vector_normalize(cylinder->dir);
	cylinder->diameter = ft_atod(array[3]);
	cylinder->height = ft_atod(array[4]);
	if (init_rgb(cylinder->rgb, array[5]))
		return (EXIT_FAILURE);
	return (0);
}
