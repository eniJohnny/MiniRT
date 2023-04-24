/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsphere_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:16:29 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 18:08:40 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_sphere	*tsphere_init(void)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->next = NULL;
	sphere->pos = NULL;
	sphere->rgb = NULL;
	sphere->diameter = 0;
	sphere->bump = -1;
	if (tsphere_allocate(sphere))
	{
		tsphere_destroy(sphere);
		return (NULL);
	}
	return (sphere);
}

int	tsphere_allocate(t_sphere *sph)
{
	sph->pos = malloc(sizeof(t_vec));
	if (!sph->pos)
		return (1);
	sph->rgb = malloc(sizeof(t_rgb));
	if (!sph->rgb)
		return (1);
	return (0);
}

void	tsphere_destroy(t_sphere *sph)
{
	if (!sph)
		return ;
	if (sph->pos)
		free(sph->pos);
	if (sph->rgb)
		free(sph->rgb);
	free(sph);
}

void	tsphere_destroy_all(t_sphere *sph)
{
	t_sphere	*tmp;

	if (!sph)
		return ;
	while (sph->next)
	{
		tmp = sph->next;
		if (sph->pos)
			free(sph->pos);
		if (sph->rgb)
			free(sph->rgb);
		free(sph);
		sph = tmp;
	}
	if (sph->pos)
		free(sph->pos);
	if (sph->rgb)
		free(sph->rgb);
	free(sph);
}

int	lst_add_back_sphere(t_program *p, char **arr)
{
	t_sphere	*sphere;
	t_sphere	*copy;

	sphere = tsphere_init();
	copy = p->sphere;
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		copy->next = sphere;
	}
	else
		p->sphere = sphere;
	if (!sphere || !check_sphere(arr))
		return (EXIT_FAILURE);
	if (init_pos(sphere->pos, arr[1]))
		return (EXIT_FAILURE);
	sphere->diameter = ft_atod(arr[2]);
	if (init_rgb(sphere->rgb, arr[3]))
		return (EXIT_FAILURE);
	if (arr[4] && ft_atoi(arr[4]) >= -2 && ft_atoi(arr[4]) < p->gui->bump_nb)
		sphere->bump = ft_atoi(arr[4]);
	return (0);
}
