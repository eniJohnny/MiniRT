/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:30:27 by johrober          #+#    #+#             */
/*   Updated: 2022/11/15 17:06:36 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_tabdup(void **tab)
{
	void	**new;
	int		i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(void *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		new[i] = tab[i];
	new[i] = NULL;
	return (new);
}
