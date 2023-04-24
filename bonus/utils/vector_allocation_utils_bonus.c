/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_allocation_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:45:51 by johrober          #+#    #+#             */
/*   Updated: 2022/11/28 14:51:11 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	*to_allocated_vector(double x, double y, double z)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		return (NULL);
	to_vector(vec, x, y, z);
	return (vec);
}

t_vec	*vector_allocated_copy(t_vec *to_copy)
{
	t_vec	*copy;

	copy = malloc(sizeof(t_vec));
	if (!copy)
		return (NULL);
	vector_copy(copy, to_copy);
	return (copy);
}

t_rgb	*to_allocated_rgb(double r, double g, double b)
{
	t_rgb	*result;

	result = malloc(sizeof(t_rgb));
	if (!result)
		return (NULL);
	to_rgb(result, r, g, b);
	return (result);
}

t_rgb	*copy_new_rgb(t_rgb *src)
{
	t_rgb	*rgb;

	if (!src)
		return (NULL);
	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		return (NULL);
	rgb->r = src->r;
	rgb->g = src->g;
	rgb->b = src->b;
	return (rgb);
}
