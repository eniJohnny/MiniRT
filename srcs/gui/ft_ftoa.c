/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:13:28 by amorel            #+#    #+#             */
/*   Updated: 2022/12/01 17:07:45 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_ftoa(float nbr)
{
	float	fpart;
	int		ipart;
	char	*str;

	str = NULL;
	if (nbr < 0)
	{
		str = ft_strcat(str, "-");
		nbr *= -1;
	}
	ipart = (int)nbr;
	fpart = nbr - (float)ipart;
	str = ft_strcat(str, ft_itoa(ipart));
	str = ft_strcat(str, ".");
	ipart = fpart * pow(10, 2);
	ipart = fmax(ipart, ipart * -1.0);
	str = ft_strcat(str, ft_itoa(ipart));
	return (str);
}

static void	ft_free_and_null(char *str)
{
	free(str);
	str = NULL;
}

char	*ft_ftoa_free(float nbr, char *to_free)
{
	float	fpart;
	int		ipart;
	char	*str;
	char	*tmp;

	str = NULL;
	if (nbr < 0)
	{
		str = ft_strcat(str, "-");
		nbr *= -1;
	}
	ipart = (int)nbr;
	fpart = nbr - (float)ipart;
	tmp = ft_itoa(ipart);
	str = ft_strcat(str, tmp);
	str = ft_strcat(str, ".");
	ipart = fpart * pow(10, 2);
	ipart = fmax(ipart, ipart * -1.0);
	free(tmp);
	tmp = ft_itoa(ipart);
	str = ft_strcat(str, tmp);
	if (to_free)
		ft_free_and_null(to_free);
	free(tmp);
	return (str);
}
