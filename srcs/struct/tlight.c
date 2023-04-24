/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:15:27 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 18:01:33 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*tlight_init(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->pos = NULL;
	light->rgb = NULL;
	light->ratio = 0;
	if (tlight_allocate(light))
	{
		tlight_destroy(light);
		return (NULL);
	}
	return (light);
}

int	tlight_allocate(t_light *light)
{
	if (!light->pos)
		light->pos = malloc(sizeof(t_vec));
	if (!light->pos)
		return (1);
	if (!light->rgb)
		light->rgb = malloc(sizeof(t_rgb));
	if (!light->rgb)
		return (1);
	return (0);
}

void	tlight_destroy(t_light *light)
{
	if (!light)
		return ;
	if (light->pos)
		free(light->pos);
	if (light->rgb)
		free(light->rgb);
	free(light);
}

int	lst_add_back_light(t_program *p, char **array)
{
	t_light	*light;

	if (p->light || !check_light(array))
		return (EXIT_FAILURE);
	light = tlight_init();
	if (!light)
		return (EXIT_FAILURE);
	p->light = light;
	if (init_pos(light->pos, array[1]))
		return (EXIT_FAILURE);
	light->ratio = ft_atod(array[2]);
	if (init_rgb(light->rgb, array[3]))
		return (EXIT_FAILURE);
	p->light = light;
	return (0);
}
