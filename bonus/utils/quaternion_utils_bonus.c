/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:23:46 by johrober          #+#    #+#             */
/*   Updated: 2022/11/05 15:36:56 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**	See "https://math.stackexchange.com/questions/1499415/
 * finding-the-quaternion-that-performs-a-rotation"
 *	(without the newline ofc) **/
t_quat	*get_allocated_quaternion(t_vec *axis, double rotation)
{
	t_quat	*result;

	result = malloc(sizeof(t_quat));
	if (!result)
		return (NULL);
	get_quaternion(result, axis, rotation);
	return (result);
}

t_quat	*get_quaternion(t_quat *result, t_vec *axis, double rotation)
{
	result->w = cos(rotation / 2.0);
	result->x = sin(rotation * axis->x / 2.0);
	result->y = sin(rotation * axis->y / 2.0);
	result->z = sin(rotation * axis->z / 2.0);
	return (result);
}

/** Apply the rotation to the provided vector. To get a new vector,
 * make a copy first. For the formula behind this, see :
 * https://gamedev.stackexchange.com/questions/28395/
 * rotating-vector3-by-a-quaternion **/
t_vec	*apply_rotation(t_vec *vec, t_quat *quat)
{
	t_vec	vquat;
	t_vec	tmp;
	t_vec	to_add;
	double	w;

	to_vector(&vquat, quat->x, quat->y, quat->z);
	w = quat->w;
	vector_copy(&tmp, &vquat);
	vector_copy(&to_add, vec);
	vector_multiplication(2.0 * dot_product(&vquat, vec), &tmp);
	vector_multiplication(w * w - dot_product(&vquat, &vquat), &to_add);
	vector_sum(&tmp, &tmp, &to_add);
	cross_product(&to_add, &vquat, vec);
	vector_multiplication(2.0 * w, &to_add);
	vector_sum(vec, &tmp, &to_add);
	return (vec);
}

/*** Multiplying two quaternions together just means creating
 * a single rotation which consists of the successive application of
 * the rotation represented by a, then b.
 * Temporary values are used in case we wanna stock the result in one
 * of the provided quaternions (which would fuck up the results if we
 * did it in one go) **/
t_quat	*quaternion_mult(t_quat *result, t_quat *a, t_quat *b)
{
	double	w;
	double	x;
	double	y;
	double	z;

	w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
	x = a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y;
	y = a->w * b->y - a->x * b->z + a->y * b->w + a->z * b->x;
	z = a->w * b->z + a->x * b->y - a->y * b->x + a->z * b->w;
	result->w = w;
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}
