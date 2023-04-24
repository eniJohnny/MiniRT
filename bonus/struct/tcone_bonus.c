/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcone_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:34:43 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 18:07:59 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_cone	*tcone_init(void)
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->next = NULL;
	cone->dir = NULL;
	cone->pos = NULL;
	cone->rgb = NULL;
	cone->angle = 0;
	cone->height = 0;
	cone->bump = -1;
	if (tcone_allocate(cone))
	{
		tcone_destroy(cone);
		return (NULL);
	}
	return (cone);
}

int	tcone_allocate(t_cone *con)
{
	con->dir = malloc(sizeof(t_vec));
	if (!con->dir)
		return (1);
	con->pos = malloc(sizeof(t_vec));
	if (!con->pos)
		return (1);
	con->rgb = malloc(sizeof(t_rgb));
	if (!con->rgb)
		return (1);
	return (0);
}

void	tcone_destroy(t_cone *con)
{
	if (!con)
		return ;
	if (con->dir)
		free(con->dir);
	if (con->pos)
		free(con->pos);
	if (con->rgb)
		free(con->rgb);
	free(con);
}

void	tcone_destroy_all(t_cone *con)
{
	t_cone	*tmp;

	if (!con)
		return ;
	while (con)
	{
		tmp = con->next;
		tcone_destroy(con);
		con = tmp;
	}
}

int	lst_add_back_cone(t_program *p, char **arr)
{
	t_cone	*cone;
	t_cone	*copy;

	cone = tcone_init();
	copy = p->cone;
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		copy->next = cone;
	}
	else
		p->cone = cone;
	if (!cone || !check_cone(arr))
		return (EXIT_FAILURE);
	if (init_rgb(cone->rgb, arr[5]))
		return (EXIT_FAILURE);
	if (init_pos(cone->pos, arr[1]) || init_vector(cone->dir, arr[2]))
		return (EXIT_FAILURE);
	vector_normalize(cone->dir);
	cone->angle = ft_atod(arr[3]);
	cone->height = ft_atod(arr[4]);
	if (arr[6] && ft_atoi(arr[6]) >= -2 && ft_atoi(arr[6]) < p->gui->bump_nb)
		cone->bump = ft_atod(arr[6]);
	return (0);
}
