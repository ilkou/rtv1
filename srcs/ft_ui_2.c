/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:57:55 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/17 12:36:35 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_check_brackets(char *s)
{
	int			b;
	int			i;

	i = 1;
	b = 0;
	while (s[i])
	{
		if (s[i] == '}')
			return (0);
		if (s[i] == '{')
		{
			b++;
			while (s[i])
			{
				i++;
				if (s[i] == '{')
					return (0);
				if (s[i] == '}')
					break ;
			}
		}
		i++;
	}
	return (s[0] && s[0] == '[' && s[i - 2] && s[i - 2] == ']' ? b : 0);
}

void		ft_check_data(t_ptr *p)
{
	t_object	*tmp;

	tmp = p->scene->object;
	if (p->scene->cam.fov < 0.0 || p->scene->cam.fov > 180.0)
		ft_free_exit("wrong field of view value\n", 1, &p);
	while (tmp)
	{
		if (tmp->size < 0.001 && tmp->hit != ft_hit_plane)
			ft_free_exit("wrong size detected\n", 1, &p);
		if (COL_TYPE(tmp->col.r) || COL_TYPE(tmp->col.g)
				|| COL_TYPE(tmp->col.b))
			ft_free_exit("wrong color format detected\n", 1, &p);
		tmp = tmp->next;
	}
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
