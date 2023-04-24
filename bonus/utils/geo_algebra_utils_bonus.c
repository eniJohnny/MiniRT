/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_algebra_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:54:32 by johrober          #+#    #+#             */
/*   Updated: 2022/11/25 15:38:06 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	dot_product(t_vec *v1, t_vec *v2)
{
	double	prod;

	prod = v1->x * v2->x;
	prod += v1->y * v2->y;
	prod += v1->z * v2->z;
	return (prod);
}

t_vec	*cross_product(t_vec *result, t_vec *v1, t_vec *v2)
{
	double	x;
	double	y;
	double	z;

	x = v1->y * v2->z - v1->z * v2->y;
	y = v1->z * v2->x - v1->x * v2->z;
	z = v1->x * v2->y - v1->y * v2->x;
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

void	vector_reflect(t_vec *result, t_vec *a, t_vec *b)
{
	double	ab;
	t_vec	tmp;

	ab = 2.0 * dot_product(a, b);
	vector_multiplication(ab, vector_copy(&tmp, b));
	vector_sub(result, &tmp, a);
}
