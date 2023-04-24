/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:17:11 by johrober          #+#    #+#             */
/*   Updated: 2022/11/30 16:36:00 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_program	*p;

	if (argc == 2 && check_arg(argv[1]))
	{
		p = tprogram_init();
		tprogram_load(p);
		if (!p)
			clean_exit(p, EXIT_FAILURE, "Fatal error\n");
		get_scene(p, argv[1]);
		if (!p->camera || !p->amblight || !p->light)
			clean_exit(p, EXIT_SUCCESS, "Closing program...\n");
		render_scene(p);
		mlx_loop(p->mlx);
		clean_exit(p, EXIT_SUCCESS, "Closing program...\n");
	}
	else
	{
		p = NULL;
		clean_exit(p, EXIT_FAILURE, "Expected arg : ./minirt scene.rt\n");
	}
	return (EXIT_SUCCESS);
}

int	check_arg(char *str)
{
	size_t	extension;

	if (!str || ft_strlen(str) < 4)
		return (0);
	extension = ft_strlen(str) - 3;
	if (!ft_strcmp(&str[extension], ".rt") && extension > 0)
		return (1);
	return (0);
}

void	clean_exit(t_program *p, int exit_code, char *prompt)
{
	if (p)
	{
		tgui_destroy(p->mlx, p->gui);
		tprogram_destroy(p);
		if (p->img)
		{
			if (p->img->image)
				mlx_destroy_image(p->mlx, p->img->image);
			free(p->img);
		}
		if (p->win)
			mlx_destroy_window(p->mlx, p->win);
		mlx_loop_end(p->mlx);
		mlx_destroy_display(p->mlx);
		free(p->mlx);
		free(p);
	}
	if (prompt)
	{
		if (exit_code == EXIT_SUCCESS)
			ft_printf_fd(1, prompt);
		else
			ft_printf_fd(2, prompt);
	}
	exit(exit_code);
}
