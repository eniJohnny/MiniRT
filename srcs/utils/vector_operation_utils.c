/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:35:04 by johrober          #+#    #+#             */
/*   Updated: 2022/11/25 15:37:52 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	*vector_sum(t_vec *result, t_vec *v1, t_vec *v2)
{
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
	return (result);
}

t_vec	*vector_fsum(float f, t_vec *v)
{
	v->x = v->x + f;
	v->y = v->y + f;
	v->z = v->z + f;
	return (v);
}

t_vec	*vector_sub(t_vec *result, t_vec *orig, t_vec *pos)
{
	result->x = orig->x - pos->x;
	result->y = orig->y - pos->y;
	result->z = orig->z - pos->z;
	return (result);
}

t_vec	*vector_multiplication(float f, t_vec *vec)
{
	vec->x = vec->x * f;
	vec->y = vec->y * f;
	vec->z = vec->z * f;
	return (vec);
}
