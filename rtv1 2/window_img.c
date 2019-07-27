/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:43:43 by mel-jadi          #+#    #+#             */
/*   Updated: 2019/04/17 23:53:29 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_mlx_putpixel(t_th *p, int x, int y, int color)
{
	if (x >= 0 && x < IMG_WIDTH && y >= 0 && y < IMG_HEIGHT)
		p->data[y * (int)IMG_WIDTH + x] = color;
}

void	ft_creat_window(t_ptr *p)
{
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, IMG_WIDTH, IMG_HEIGHT, "rtv1");
}

void	ft_creat_image(t_ptr *p)
{
	p->img = mlx_new_image(p->mlx, IMG_WIDTH, IMG_HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, p->bpp, p->size, p->endian);
}

void	ft_copy(t_ptr *p, t_th *th)
{
	th->spec = p->spec;
	th->maxref = p->maxref;
	th->pref = p->pref;
	th->cpt = 0;
	th->cam_pos = (t_vec){p->cam_pos.x, p->cam_pos.y, p->cam_pos.z};
	th->cam_dir = (t_vec){p->cam_dir.x, p->cam_dir.y, p->cam_dir.z};
	th->ray_dir = (t_vec){p->ray_dir.x, p->ray_dir.y, p->ray_dir.z};
	th->light = copy_obj(p->light);
	th->obj = copy_obj(p->obj);
	th->data = p->data;
	th->aa = p->aa;
}

t_obj    *copy_obj(t_obj *obj)
{
    t_obj    *newlist;
    
    if (!(newlist = (t_obj *)malloc(sizeof(t_obj))))
        return (NULL);
    if (obj && newlist)
    {
        newlist->type = obj->type;
        newlist->size = obj->size;
        newlist->rot = (t_vec){obj->rot.x, obj->rot.y, obj->rot.z};
        newlist->pos = (t_vec){obj->pos.x, obj->pos.y, obj->pos.z};
        newlist->col.red = obj->col.red;
        newlist->col.green = obj->col.green;
        newlist->col.blue = obj->col.blue;
        newlist->next = NULL;
        if (newlist && obj->next)
            newlist->next = copy_obj(obj->next);
        return (newlist);
    }
    return (NULL);
}
