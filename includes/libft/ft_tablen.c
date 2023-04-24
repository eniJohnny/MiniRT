/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:55:20 by rrollin           #+#    #+#             */
/*   Updated: 2022/07/02 16:16:50 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_tablen(const void **tab)
{
	int	len;

	len = 0;
	while (tab && tab[len])
		len++;
	return (len);
}