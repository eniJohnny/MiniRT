/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:55:24 by johrober          #+#    #+#             */
/*   Updated: 2022/11/01 22:55:15 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	result_size;
	size_t	count;

	result_size = 0;
	count = 0;
	while (dest[result_size] && result_size < size)
		result_size++;
	if (result_size < size)
	{
		while (src[count] && result_size < size - 1)
		{
			dest[result_size] = src[count];
			result_size++;
			count++;
		}
		dest[result_size] = 0;
	}
	while (src[count])
	{
		result_size++;
		count++;
	}
	return (result_size);
}
