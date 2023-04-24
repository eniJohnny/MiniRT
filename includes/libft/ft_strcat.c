/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:54:45 by amorel            #+#    #+#             */
/*   Updated: 2022/11/05 15:39:59 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *base, char *cat)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(ft_strlen(base) + ft_strlen(cat) + 1);
	while (base && base[i])
	{
		buffer[i] = base[i];
		i++;
	}
	while (cat[j])
	{
		buffer[i + j] = cat[j];
		j++;
	}
	buffer[i + j] = 0;
	free(base);
	return (buffer);
}
