/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:57:55 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 18:05:12 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_from_rgb(int x, int y, int z)
{
	t_point r;
	t_point g;
	t_point b;

	r.y = x % 16;
	r.x = (x / 16) % 16;
	g.y = y % 16;
	g.x = (y / 16) % 16;
	b.y = z % 16;
	b.x = (z / 16) % 16;
	return ((int)r.x * 16 * 16 * 16 * 16 * 16 + (int)r.y * 16 * 16 * 16 * 16 +
			(int)g.x * 16 * 16 * 16 + (int)g.y * 16 * 16 +
			(int)b.x * 16 + (int)b.y);
}

void		ft_object_selected(t_ptr *p)
{
	char	*size;
	char	*col;
	char	*pos;
	char	*rot;

	size = ft_dtoa(PS->curr_object->size);
	col = ft_ctoa(PS->curr_object->col);
	pos = ft_vtoa(PS->curr_object->pos);
	rot = ft_vtoa(PS->curr_object->rot);
	MSP(p->mlx, p->win, FRAME + 110, FRAME + 10, COL2, PS->curr_object->name);
	MSP(p->mlx, p->win, FRAME + 110, FRAME + 30, COL2, pos);
	MSP(p->mlx, p->win, FRAME + 110, FRAME + 50, COL2, rot);
	MSP(p->mlx, p->win, FRAME + 110, FRAME + 70, COL2, col);
	MSP(p->mlx, p->win, FRAME + 110, FRAME + 90, COL2, size);
	free(size);
	free(col);
	free(pos);
	free(rot);
}

void		ft_display_properties(t_ptr *p)
{
	char	*cam;
	char	*theta;
	char	*anti_a;
	char	*spec;
	char	*shininess;

	cam = ft_vtoa(PS->cam.origin);
	theta = ft_dtoa(PS->theta);
	anti_a = ft_dtoa(PS->anti_a);
	spec = PS->spec ? ft_strdup("On") : ft_strdup("Off");
	shininess = ft_dtoa(PS->shininess);
	MSP(p->mlx, p->win, FRAME + 510, FRAME + 10, COL2, cam);
	MSP(p->mlx, p->win, FRAME + 510, FRAME + 30, COL2, theta);
	MSP(p->mlx, p->win, FRAME + 510, FRAME + 50, COL2, anti_a);
	MSP(p->mlx, p->win, FRAME + 510, FRAME + 70, COL2, spec);
	MSP(p->mlx, p->win, FRAME + 510, FRAME + 90, COL2, shininess);
	free(cam);
	free(theta);
	free(anti_a);
	free(spec);
	free(shininess);
}

void		ft_display_moves(t_ptr *p)
{
	if (p->inc_dec == 1)
	{
		MSP(p->mlx, p->win, FRAME + 710, FRAME + 10, COL2, "Increase/");
		MSP(p->mlx, p->win, FRAME + 800, FRAME + 10, COL1, "Decrease");
	}
	else
	{
		MSP(p->mlx, p->win, FRAME + 710, FRAME + 10, COL1, "Increase/");
		MSP(p->mlx, p->win, FRAME + 800, FRAME + 10, COL2, "Decrease");
	}
	MSP(p->mlx, p->win, FRAME + 640, FRAME + 30, COL1,
			"[X|Y|Z]: Rotation about x/y/z axis");
	MSP(p->mlx, p->win, FRAME + 640, FRAME + 50, COL1, "[<X>|^Yv|-Z+]: Move");
	MSP(p->mlx, p->win, FRAME + 640, FRAME + 70, COL1, "[C]: Camera ");
	(p->cam_slct) ?
		MSP(p->mlx, p->win, FRAME + 760, FRAME + 70, COL2, "Selected") :
		MSP(p->mlx, p->win, FRAME + 760, FRAME + 70, COL1, "Unselected");
	MSP(p->mlx, p->win, FRAME + 640, FRAME + 90, COL1, "[L]: Lights ");
	(p->light_slct) ?
		MSP(p->mlx, p->win, FRAME + 760, FRAME + 90, COL2, "Selected") :
		MSP(p->mlx, p->win, FRAME + 760, FRAME + 90, COL1, "Unselected");
}
