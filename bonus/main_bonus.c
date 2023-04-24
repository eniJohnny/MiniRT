/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:17:11 by johrober          #+#    #+#             */
/*   Updated: 2022/12/12 15:55:56 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	main(int argc, char **argv)
{
	t_program	*p;

	(void)argv;
	p = NULL;
	if (argc == 2 && is_valid_extension(argv[1], ".rt"))
	{
		p = tprogram_init();
		tprogram_load(p);
		if (!p)
			clean_exit(p, EXIT_FAILURE, "Fatal error\n");
		if (!p->gui)
			clean_exit(p, EXIT_FAILURE, "Fatal gui error\n");
		if (!p->map)
			clean_exit(p, EXIT_FAILURE, "Fatal map error\n");
		get_scene(p, argv[1]);
		if (!p->camera || !p->amblight || !p->light)
			clean_exit(p, EXIT_SUCCESS, "Closing program...\n");
		render_scene(p);
		mlx_loop(p->mlx);
		clean_exit(p, EXIT_SUCCESS, "Closing program...\n");
	}
	else
		clean_exit(p, EXIT_FAILURE, "Expected arg : ./minirt scene.rt\n");
	return (EXIT_SUCCESS);
}

int	is_valid_extension(char *str, char *extension)
{
	size_t	index;

	if (!str || !extension || ft_strlen(str) < ft_strlen(extension))
		return (0);
	index = ft_strlen(str) - ft_strlen(extension);
	if (!ft_strcmp(&str[index], extension) && index > 0)
		return (1);
	return (0);
}

void	clean_exit(t_program *p, int exit_code, char *prompt)
{
	if (p)
	{
		tprogram_destroy(p);
		tgui_destroy(p->mlx, p->gui);
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
