/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multiple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:43:53 by amorel            #+#    #+#             */
/*   Updated: 2022/11/21 16:31:34 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c, char *separators)
{
	int	i;

	i = -1;
	while (separators[++i])
	{
		if (separators[i] == c)
			return (1);
	}
	return (0);
}

static int	to_next_split(char const *s, char *separators, int i)
{
	int	n;

	n = i;
	if (!separators || !s || !s[i])
		return (0);
	while (s[i] && !is_separator(s[i], separators))
	{
		i++;
	}
	return (i - n);
}

static char	**tabdup_and_add(char **mtx, char *str)
{
	char	**new;
	int		i;

	if (!str)
		return (mtx);
	i = 0;
	while (mtx && mtx[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (mtx);
	i = -1;
	if (!mtx)
		i++;
	while (mtx && mtx[++i])
		new[i] = mtx[i];
	new[i] = str;
	new[i + 1] = NULL;
	free(mtx);
	return (new);
}

char	**ft_split_multiple(char const *s, char *separators)
{
	char	**mtx;
	char	*buffer;
	int		i;

	if (s == NULL || separators == NULL)
		return (NULL);
	i = 0;
	mtx = NULL;
	while (s[i])
	{
		buffer = malloc(sizeof(char) * (to_next_split(s, separators, i) + 1));
		if (buffer)
		{
			ft_strlcpy(buffer, &s[i], to_next_split(s, separators, i) + 1);
			mtx = tabdup_and_add(mtx, buffer);
			i += to_next_split(s, separators, i);
		}
		while (is_separator(s[i], separators))
			i++;
	}
	return (mtx);
}
