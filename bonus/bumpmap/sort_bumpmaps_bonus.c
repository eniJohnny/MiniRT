/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bumpmaps_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:19:23 by amorel            #+#    #+#             */
/*   Updated: 2022/11/21 15:43:53 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	swap_bm(t_bumpmap **bm, int i, int j)
{
	t_bumpmap	*tmp;

	tmp = bm[j];
	bm[j] = bm[i];
	bm[i] = tmp;
}

static void	swap_name(char **bnames, int i, int j)
{
	char	*tmp;

	tmp = ft_strdup(bnames[i]);
	if (!tmp)
		return ;
	free(bnames[i]);
	bnames[i] = ft_strdup(bnames[j]);
	if (!bnames[i])
		return ;
	free(bnames[j]);
	bnames[j] = tmp;
}

static int	bm_ordered(char **bnames, int nb)
{
	int	i;

	i = -1;
	while (++i < nb - 1)
		if (ft_strcmp(bnames[i], bnames[i + 1]) > 0)
			return (0);
	return (1);
}

void	sort_bumpmaps(t_program *p)
{
	int	i;
	int	j;

	while (!bm_ordered(p->gui->bump_names, p->gui->bump_nb))
	{
		j = -1;
		while (++j < p->gui->bump_nb)
		{
			i = -1;
			while (++i < j)
			{
				if (ft_strcmp(p->gui->bump_names[j], p->gui->bump_names[i]) < 0)
				{
					swap_bm(p->bm, i, j);
					swap_name(p->gui->bump_names, i, j);
				}
			}
		}
	}
}
