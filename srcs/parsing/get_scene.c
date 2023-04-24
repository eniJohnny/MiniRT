/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:37:27 by amorel            #+#    #+#             */
/*   Updated: 2022/12/12 16:20:27 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	finish_reading_and_free(int file, char **array)
{
	char	*str;

	str = NULL;
	str = get_next_line(file);
	while (str)
	{
		free(str);
		str = get_next_line(file);
	}
	ft_free_tab((void **)array);
	close(file);
}

static int	array_to_structure(t_program *program, char **array)
{
	if (!ft_strcmp(array[0], "A"))
		return (lst_add_back_amblight(program, array));
	else if (!ft_strcmp(array[0], "C"))
		return (lst_add_back_camera(program, array));
	else if (!ft_strcmp(array[0], "L"))
		return (lst_add_back_light(program, array));
	else if (!ft_strcmp(array[0], "sp"))
		return (lst_add_back_sphere(program, array));
	else if (!ft_strcmp(array[0], "pl"))
		return (lst_add_back_plane(program, array));
	else if (!ft_strcmp(array[0], "cy"))
		return (lst_add_back_cylinder(program, array));
	else if (!ft_strcmp(array[0], "\n"))
		return (0);
	return (EXIT_FAILURE);
}

void	get_scene(t_program *program, char *filepath)
{
	int		file;
	char	*str;
	char	**array;

	file = open(filepath, O_RDONLY);
	if (file == -1)
		clean_exit(program, EXIT_FAILURE, "invalid scene\n");
	while (1)
	{
		str = get_next_line(file);
		if (!str)
		{
			close(file);
			break ;
		}
		array = ft_split_multiple(str, " \t");
		free(str);
		if (array_to_structure(program, array))
		{
			finish_reading_and_free(file, array);
			clean_exit(program, EXIT_FAILURE, "Parsing error\n");
		}
		ft_free_tab((void **) array);
	}
}
