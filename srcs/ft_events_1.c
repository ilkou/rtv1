/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:06:06 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 18:59:05 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

void		ft_cam_rotation(int key, t_ptr *p)
{
	if (key == MLX_KEY_X)
		PS->cam.origin = ft_rotcam_x(PS->cam.origin, p->inc_dec
				* DEG_TO_RAD(PS->theta));
	if (key == MLX_KEY_Y)
		PS->cam.origin = ft_rotcam_y(PS->cam.origin, p->inc_dec
				* DEG_TO_RAD(PS->theta));
	PS->cam = ft_init_camera(PS->cam.origin, PS->cam.lookat, PS->cam.fov);
}

void		ft_cam_light_event(int key, t_ptr *p)
{
	if (key == MLX_KEY_C)
	{
		p->cam_slct = p->cam_slct == 0 ? 1 : 0;
		p->light_slct = p->cam_slct == 1 ? 0 : p->light_slct;
		PS->curr_object = NULL;
	}
	if (key == MLX_KEY_L && PS->light)
	{
		if (p->light_slct == 0)
		{
			p->curr_light = PS->light;
			p->light_slct = 1;
		}
		else if (p->curr_light->next != NULL)
			p->curr_light = p->curr_light->next;
		else
		{
			p->curr_light = NULL;
			p->light_slct = 0;
		}
		p->cam_slct = p->light_slct == 1 ? 0 : p->cam_slct;
		PS->curr_object = NULL;
	}
}

void		ft_slot(int key, t_ptr *p)
{
	if (key == MLX_KEY_D && PS->curr_object != NULL && PS->object->next != NULL)
		ft_delete_object(&PS->object, &PS->curr_object);
	if (p->cam_slct && (key == MLX_KEY_X || key == MLX_KEY_Y))
		ft_cam_rotation(key, p);
	if (ft_menu_event(key, p))
		ft_background(p);
	else
		ft_draw(p);
}

int			ft_deal_key(int key, t_ptr *p)
{
	t_vector	*pos;

	pos = NULL;
	if (key == MLX_KEY_ESC)
		ft_close(p);
	ft_selected_event(key, p);
	ft_cam_light_event(key, p);
	pos = (p->cam_slct) ? &PS->cam.origin : pos;
	pos = (p->light_slct) ? &p->curr_light->pos : pos;
	pos = (PS->curr_object != NULL) ? &PS->curr_object->pos : pos;
	if (key == MLX_KEY_LEFT && pos)
		pos->v1 -= 0.1;
	if (key == MLX_KEY_RIGHT && pos)
		pos->v1 += 0.1;
	if (key == MLX_KEY_UP && pos)
		pos->v2 += 0.1;
	if (key == MLX_KEY_DOWN && pos)
		pos->v2 -= 0.1;
	if (key == MLX_KEY_PLUS && pos)
		pos->v3 += 0.1;
	if (key == MLX_KEY_MINUS && pos)
		pos->v3 -= 0.1;
	ft_slot(key, p);
	return (key);
}

int			ft_mouse_press(int button, int x, int y, t_ptr *p)
{
	if (button == 1 && COND_SELECT(x, y))
	{
		ft_select_obj(p, x - FRAME, (int)IMG_HEIGHT - (y - MENU_BAR));
		if (PS->curr_object != NULL)
		{
			p->light_slct = 0;
			p->cam_slct = 0;
		}
	}
	if (button == 2)
		PS->curr_object = NULL;
	ft_background(p);
	return (0);
}
