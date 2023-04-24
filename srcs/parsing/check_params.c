/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:42:02 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 18:45:21 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_correct_float(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-')
		{
			return (0);
		}
	}
	return (1);
}

int	check_rgb_parsing(char *str)
{
	char	**mtx;
	int		i;

	i = -1;
	if (!str)
		return (0);
	mtx = ft_split(str, ',');
	if (!mtx)
		return (0);
	while (++i < 3)
	{
		if (!mtx[i] || ft_atod(mtx[i]) < 0 || ft_atod(mtx[i]) > 255)
		{
			ft_free_tab((void **) mtx);
			return (0);
		}
	}
	if (mtx[i])
	{
		ft_free_tab((void **) mtx);
		return (0);
	}
	ft_free_tab((void **) mtx);
	return (1);
}

int	check_ratio_parsing(char *str)
{
	if (!str || !is_correct_float(str) || ft_atod(str) < 0 || ft_atod(str) > 1)
		return (0);
	return (1);
}

int	check_size_parsing(char *str)
{
	if (!str || !is_correct_float(str) || ft_atod(str) <= 0)
		return (0);
	return (1);
}

int	check_vector_parsing(char *str, int isnormalized)
{
	char	**mtx;
	int		i;

	i = -1;
	if (!str)
		return (0);
	mtx = ft_split(str, ',');
	if (!mtx)
		return (0);
	while (++i < 3)
	{
		if (!mtx[i] || !is_correct_float(mtx[i]) || (isnormalized == 1
				&& (ft_atof(mtx[i]) < -1 || ft_atof(mtx[i]) > 1)))
		{
			ft_free_tab((void **) mtx);
			return (0);
		}
	}
	i = 1;
	if (mtx[3] || (isnormalized == 1 && ft_atof(mtx[0]) == 0.0
			&& ft_atof(mtx[1]) == 0.0 && ft_atof(mtx[2]) == 0.0))
		i = 0;
	ft_free_tab((void **) mtx);
	return (i);
}
