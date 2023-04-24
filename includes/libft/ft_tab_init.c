/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:14:06 by johrober          #+#    #+#             */
/*   Updated: 2022/11/14 16:49:47 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_allocated_cells(void **tab, int x)
{
	int	count;

	count = -1;
	while (++count < x)
		free(tab[count]);
}

static int	init_level(void **tab, int nb, int width, int level)
{
	int	x;

	x = -1;
	while (++x < nb)
	{
		if (level > 0)
		{
			tab[x] = malloc(sizeof(void *) * (width + 1));
			if (!tab[x])
			{
				free_allocated_cells(tab, x);
				return (1);
			}
		}
		else
			tab[x] = NULL;
	}
	tab[x] = NULL;
	return (0);
}

static int	init_dimension(void **tab, int nb, int level, va_list args)
{
	int		x;
	int		width;

	if (level > 0)
		width = va_arg(args, int);
	if (init_level(tab, nb, width, level))
		return (1);
	x = -1;
	while (level > 0 && ++x < nb)
	{
		if (init_dimension(tab[x], width, level - 1, args))
		{
			level = -1;
			break ;
		}
	}
	if (level == -1)
	{
		while (--x >= 0)
			ft_free_tab(tab[x]);
		return (1);
	}
	return (0);
}

void	**ft_tab_init(int levels, int width, ...)
{
	va_list	args;
	void	**tab;

	tab = NULL;
	va_start(args, width);
	if (levels >= 1)
	{
		tab = malloc(sizeof(void *) * (width + 1));
		if (tab && init_dimension(tab, width, levels - 1, args))
		{
			free(tab);
			tab = NULL;
		}
	}
	va_end(args);
	return (tab);
}
