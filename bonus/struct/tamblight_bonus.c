/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tamblight_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:12:09 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 18:12:03 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_amblight	*tamblight_init(void)
{
	t_amblight	*amblight;

	amblight = malloc(sizeof(t_amblight));
	if (!amblight)
		return (NULL);
	amblight->ratio = 0;
	amblight->rgb = NULL;
	if (tamblight_allocate(amblight))
	{
		tamblight_destroy(amblight);
		return (NULL);
	}
	return (amblight);
}

int	tamblight_allocate(t_amblight *amb)
{
	amb->rgb = malloc(sizeof(t_rgb));
	if (!amb->rgb)
		return (1);
	return (0);
}

void	tamblight_destroy(t_amblight *amb)
{
	if (!amb)
		return ;
	if (amb->rgb)
		free(amb->rgb);
	free(amb);
}

int	lst_add_back_amblight(t_program *p, char **array)
{
	t_amblight	*amblight;

	if (p->amblight || !check_amblight(array))
		return (1);
	amblight = tamblight_init();
	p->amblight = amblight;
	if (!amblight)
		return (1);
	amblight->ratio = ft_atod(array[1]);
	init_rgb(amblight->rgb, array[2]);
	return (0);
}
