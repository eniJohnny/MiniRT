/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:51:37 by johrober          #+#    #+#             */
/*   Updated: 2022/12/01 15:46:34 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	count;
	size_t	length;

	length = ft_strlen(str);
	dup = malloc((length + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	count = 0;
	while (count < length)
	{
		dup[count] = str[count];
		count++;
	}
	dup[count] = 0;
	return (dup);
}
