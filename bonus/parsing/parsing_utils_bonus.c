/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:02:13 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 14:32:52 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	init_pos(t_vec *pos, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (EXIT_FAILURE);
	pos->x = ft_atod(split[0]);
	pos->y = ft_atod(split[1]);
	pos->z = ft_atod(split[2]);
	ft_free_tab((void **) split);
	return (0);
}

int	init_vector(t_vec *vector, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (EXIT_FAILURE);
	vector->x = ft_atod(split[0]);
	vector->y = ft_atod(split[1]);
	vector->z = ft_atod(split[2]);
	ft_free_tab((void **) split);
	return (0);
}

int	init_rgb(t_rgb *rgb, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (EXIT_FAILURE);
	rgb->r = ft_atod(split[0]) / 255;
	rgb->g = ft_atod(split[1]) / 255;
	rgb->b = ft_atod(split[2]) / 255;
	ft_free_tab((void **) split);
	return (0);
}
