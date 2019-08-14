/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:06:06 by oouklich          #+#    #+#             */
/*   Updated: 2019/03/23 11:52:24 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_close(t_ptr *p)
{
    mlx_destroy_image(p->mlx, p->img);
    mlx_destroy_window(p->mlx, p->win);
    free(p->bpp);
    free(p->size);
    free(p->endian);
    ft_free_exit("", 0, &p);
    exit(0);
    return (0);
}
int        ft_delete_object(t_object **list, t_object **to_delete)
{
    t_object *temp;
    t_object *next;

    temp = *list;
    if (temp->next == NULL)
        return (0);
    if (temp == *to_delete)
    {
        *list = temp->next;
        free(temp);
        *to_delete = NULL;
        return (1);
    }
    while (temp)
    {
        if (temp->next && temp->next == *to_delete)
            break;
        temp = temp->next;
    }
    next = temp->next->next;
    free(temp->next);
    temp->next = next;
    *to_delete = NULL;
    return (2);
}
int         ft_selected_event(int key, t_ptr *p)
{
    t_object *tmp;

    tmp = PS->object;
    while (tmp && PS->curr_object != NULL)
    {
        if (tmp == PS->curr_object)
            break;
        tmp = tmp->next;
    }
    if (key == MLX_KEY_X && PS->curr_object != NULL)
        tmp->rot = ft_rot_x(tmp->rot, p->inc_dec * DEG_TO_RAD(PS->theta));
    if (key == MLX_KEY_Y && PS->curr_object != NULL)
        tmp->rot = ft_rot_y(tmp->rot, p->inc_dec * DEG_TO_RAD(PS->theta));
    if (key == MLX_KEY_Z && PS->curr_object != NULL)
        tmp->rot = ft_rot_z(tmp->rot, p->inc_dec * DEG_TO_RAD(PS->theta));
    if (key == MLX_KEY_S)
        PS->spec = PS->spec ? 0 : 1;
    if (key == MLX_KEY_B)
        PS->brillance = p->inc_dec > 0 ? PS->brillance + 5 : PS->brillance - 5;
    if (key == MLX_KEY_A)
        PS->anti_a = p->inc_dec > 0 ? PS->anti_a * 2.0 : PS->anti_a / 2.0;
    return (1);
}

int         ft_menu_event(int key, t_ptr *p)
{
    if (key == MLX_KEY_O && p->inc_dec == 1)
        PS->theta = PS->theta + 10.0 < 180.0 ? PS->theta + 10.0 : -180.0;
    if (key == MLX_KEY_O && p->inc_dec == -1)
        PS->theta = PS->theta - 10.0 > -180.0 ? PS->theta - 10.0 : 180.0;
    if (key == MLX_KEY_ENTER)
        p->inc_dec = p->inc_dec == 1 ? -1 : 1;
    return (key == MLX_KEY_O || key == MLX_KEY_ENTER);
}
int         ft_cam_light_event(int key, t_ptr *p)
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
        else {
            p->curr_light = NULL;
            p->light_slct = 0;
        }
        p->cam_slct = p->light_slct == 1 ? 0 : p->cam_slct;
        PS->curr_object = NULL;
    }
    return (1);
}
int			ft_deal_key(int key, t_ptr *p)
{
    t_vector *pos;

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
    if (key == MLX_KEY_D && PS->curr_object != NULL)
        ft_delete_object(&PS->object, &PS->curr_object);
    PS->cam = ft_init_camera(PS->cam.origin, PS->cam.lookat, PS->cam.fov);
    if (ft_menu_event(key, p))
        ft_background(p);
    else
        ft_draw(p);
	return (key);
}

void   ft_select_obj(t_ptr *p, int col, int row)
{
    t_ray   r;

    r = ft_get_ray(&PS->cam, col, row);
    if (ft_hit(PS->object, r, I(0.0001, DBL_MAX), &PS->record))
        PS->curr_object = PS->record.curr_obj;
    else
        PS->curr_object = NULL;
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
