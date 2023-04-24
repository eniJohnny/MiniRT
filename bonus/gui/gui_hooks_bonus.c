/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:23:58 by amorel            #+#    #+#             */
/*   Updated: 2022/12/09 16:35:17 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	amblight_hook(int x, int y, t_program *p)
{
	if (x >= 55 && x <= 87 && y >= 69 && y <= 85)
		change_amb_ratio(p, x);
	else if (x >= 30 && x <= 62 && y >= 99 && y <= 115)
		change_amb_rgb(p, x, 'r');
	else if (x >= 30 && x <= 62 && y >= 123 && y <= 139)
		change_amb_rgb(p, x, 'g');
	else if (x >= 30 && x <= 62 && y >= 147 && y <= 162)
		change_amb_rgb(p, x, 'b');
}

void	light_hook(int x, int y, t_program *p)
{
	if (x >= 55 && x <= 87 && y >= 69 && y <= 85)
		change_light_ratio(p, x);
	else if (x >= 70 && x <= 102 && y >= 98 && y <= 114)
		change_light_pos(p, x, 'x');
	else if (x >= 70 && x <= 102 && y >= 122 && y <= 137)
		change_light_pos(p, x, 'y');
	else if (x >= 70 && x <= 102 && y >= 146 && y <= 168)
		change_light_pos(p, x, 'z');
	else if (x >= 30 && x <= 62 && y >= 191 && y <= 207)
		change_light_rgb(p, x, 'r');
	else if (x >= 30 && x <= 62 && y >= 215 && y <= 230)
		change_light_rgb(p, x, 'g');
	else if (x >= 30 && x <= 62 && y >= 239 && y <= 255)
		change_light_rgb(p, x, 'b');
}

static void	get_light_nb(t_program *p, int id)
{
	t_light	*tmp;
	t_hit	*hit;

	hit = malloc(sizeof(t_hit));
	if (!hit)
		return ;
	tmp = p->light;
	while (--id >= 0)
		tmp = tmp->next;
	p->gui->light_id = (p->gui->light_id + 1) % (p->gui->light_nb);
	hit->type = LIGHT;
	hit->object = (t_light *)tmp;
	print_light(p, hit);
}

int	gui_hook_key(int keycode, t_program *p)
{
	t_hit	*hit;
	int		*bump;

	bump = NULL;
	if (keycode == XK_l)
		get_light_nb(p, p->gui->light_id);
	else if (keycode == XK_o)
	{
		hit = malloc(sizeof(t_hit));
		if (!hit)
			return (1);
		hit->type = AMBLIGHT;
		hit->object = (t_amblight *)p->amblight;
		print_amblight(p, hit);
	}
	else if (keycode == XK_t && p->gui->selection
		&& p->gui->selection->type != NONE
		&& p->gui->selection->type != LIGHT
		&& p->gui->selection->type != AMBLIGHT)
	{
		increment_and_print(p, bump);
	}
	return (0);
}
