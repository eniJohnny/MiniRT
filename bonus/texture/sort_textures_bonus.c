/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:50:50 by amorel            #+#    #+#             */
/*   Updated: 2022/11/21 15:44:06 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	swap_tx(t_img **tx, int i, int j)
{
	t_img	*tmp;

	tmp = tx[j];
	tx[j] = tx[i];
	tx[i] = tmp;
}

static void	swap_name(char **tnames, int i, int j)
{
	char	*tmp;

	tmp = ft_strdup(tnames[i]);
	if (!tmp)
		return ;
	free(tnames[i]);
	tnames[i] = ft_strdup(tnames[j]);
	if (!tnames[i])
		return ;
	free(tnames[j]);
	tnames[j] = tmp;
}

static int	tx_ordered(char **tnames, int nb)
{
	int	i;

	i = -1;
	while (++i < nb - 1)
		if (ft_strcmp(tnames[i], tnames[i + 1]) > 0)
			return (0);
	return (1);
}

void	sort_textures(t_program *p)
{
	int	i;
	int	j;

	while (!tx_ordered(p->gui->texture_names, p->gui->bump_nb))
	{
		j = -1;
		while (++j < p->gui->bump_nb)
		{
			i = -1;
			while (++i < j)
			{
				if (ft_strcmp(p->gui->texture_names[j], \
					p->gui->texture_names[i]) < 0)
				{
					swap_tx(p->textures, i, j);
					swap_name(p->gui->texture_names, i, j);
				}
			}
		}
	}
}
