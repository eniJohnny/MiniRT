/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:21:40 by johrober          #+#    #+#             */
/*   Updated: 2022/11/16 15:50:39 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_free_tab(void **tab)
{
	int	count;

	count = 0;
	if (!tab)
		return (NULL);
	while (tab[count] != NULL)
	{
		free(tab[count]);
		count++;
	}
	free(tab);
	return (NULL);
}
