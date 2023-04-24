/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basics_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:50:10 by johrober          #+#    #+#             */
/*   Updated: 2022/11/28 14:51:35 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	*get_vector_norm(t_vec *vec)
{
	t_vec	*result;

	result = vector_allocated_copy(vec);
	vector_normalize(result);
	return (result);
}

t_vec	*vector_normalize(t_vec *vec)
{
	double	k;

	k = sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
	if (!k)
		return (to_vector(vec, 0, 0, 0));
	vector_multiplication(1.0 / k, vec);
	return (vec);
}

t_vec	*to_vector(t_vec *result, double x, double y, double z)
{
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

t_vec	*vector_copy(t_vec *result, t_vec *to_copy)
{
	to_vector(result, to_copy->x, to_copy->y, to_copy->z);
	return (result);
}

t_rgb	*to_rgb(t_rgb *result, double r, double g, double b)
{
	result->r = r;
	result->g = g;
	result->b = b;
	return (result);
}
