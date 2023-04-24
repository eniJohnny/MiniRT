/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_print_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:41:59 by amorel            #+#    #+#             */
/*   Updated: 2022/11/21 16:03:18 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	print_amblight(t_program *p, t_hit *hit)
{
	t_amblight	*amb;
	char		*str;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_amblight_imgs(p->mlx, p->gui);
	amb = (t_amblight *)(hit->object);
	str = NULL;
	str = ft_ftoa_free(amb->ratio, str);
	mlx_string_put(p->mlx, p->gui->win, 100, 81, WHITE, str);
	str = ft_ftoa_free(amb->rgb->r, str);
	mlx_string_put(p->mlx, p->gui->win, 76, 111, WHITE, str);
	str = ft_ftoa_free(amb->rgb->g, str);
	mlx_string_put(p->mlx, p->gui->win, 76, 135, WHITE, str);
	str = ft_ftoa_free(amb->rgb->b, str);
	mlx_string_put(p->mlx, p->gui->win, 76, 159, WHITE, str);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
	free(str);
}

void	print_light(t_program *p, t_hit *hit)
{
	t_light	*light;
	char	*str;

	clear_screen(p->mlx, p->gui->win, p->gui->imgs[BG]->image);
	blit_light_imgs(p->mlx, p->gui);
	light = (t_light *)(hit->object);
	str = NULL;
	print_to_gui(p, light->ratio, 100, 81);
	print_to_gui(p, light->pos->x, 116, 111);
	print_to_gui(p, light->pos->y, 116, 135);
	print_to_gui(p, light->pos->z, 116, 159);
	print_to_gui(p, light->rgb->r, 76, 204);
	print_to_gui(p, light->rgb->g, 76, 228);
	print_to_gui(p, light->rgb->b, 76, 252);
	if (p->gui->selection && p->gui->selection != hit)
		free (p->gui->selection);
	p->gui->selection = hit;
	free(str);
}
