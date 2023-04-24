/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:17:53 by amorel            #+#    #+#             */
/*   Updated: 2022/11/22 13:57:24 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_instructions(void)
{
	printf("\n----Active window : MiniRT----\n");
	printf("- WASD to move the camera\n");
	printf("- QE to move the camera down / up\n");
	printf("- ARROWS to rotate the camera\n");
	printf("\n-----Active window : GUI-----\n");
	printf("- O to edit ambiant light\n");
	printf("- L to edit lights\n");
}

static void	cast_rays(t_program *p)
{
	int		i;
	int		j;

	j = 0;
	while (j < HEIGHT - 1)
	{
		i = 0;
		while (i < WIDTH - 1)
		{
			cast_single_ray(&p->map[j][i], p, p->rays[j][i]);
			i++;
		}
		j++;
		if ((j + 1) % 9 == 0)
		{
			write(1, "\r", 1);
			ft_putnbr_fd((j + 1) / 9, 1);
			write(1, "\% ", 2);
		}
	}
}

void	render_scene(t_program *p)
{
	if (p->rays)
		free_rays(p->rays);
	p->rays = get_camera_rays(p->camera);
	if (!p->rays)
		return ;
	print_instructions();
	cast_rays(p);
	render(p, p->map);
	printf("\tprint done\n");
	printf("\nDon't forget to hit refresh ;)\n");
}
