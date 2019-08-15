/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:02:31 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 17:53:53 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

double		ft_clamping(double value)
{
	if (value < 0.0)
		value = 0.0;
	if (value > 1.0)
		value = 1.0;
	return (value);
}

void		ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
	if (x >= 0 && x < IMG_WIDTH
			&& y >= 0 && y < IMG_HEIGHT)
	{
		p->data[y * (int)IMG_WIDTH + x] = color;
	}
}

t_camera	ft_init_camera(t_vector lookfrom, t_vector lookat, double vfov)
{
	t_camera	c;
	t_vector	vup;

	vup = VEC(0, 1, 0);
	c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
	c.half_w = (IMG_WIDTH / IMG_HEIGHT) * c.half_h;
	c.origin = lookfrom;
	c.w = ft_normalize(ft_sub(lookat, lookfrom));
	c.u = ft_normalize(ft_cross(c.w, vup));
	c.v = ft_cross(c.u, c.w);
	c.lower_left_corner = ft_sub(c.origin, ft_add(ft_pro_k(c.v, c.half_h),
				ft_pro_k(c.u, c.half_w)));
	c.lower_left_corner = ft_add(c.lower_left_corner, c.w);
	c.horizontal = ft_pro_k(c.u, 2.0 * c.half_w);
	c.vertical = ft_pro_k(c.v, 2.0 * c.half_h);
	c.fov = vfov;
	c.lookat = lookat;
	return (c);
}

t_scene		*ft_init_scene(void)
{
	t_scene		*scene;

	if (!(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		return (NULL);
	scene->anti_a = 3.0;
	scene->object = NULL;
	scene->light = NULL;
	scene->pd = 0.6;
	scene->shininess = 30.0;
	scene->spec = 1;
	scene->theta = 2.5;
	scene->curr_object = NULL;
	return (scene);
}

void		ft_init(t_ptr *p)
{
	p->img = NULL;
	p->mlx = NULL;
	p->data = NULL;
	p->win = NULL;
	p->bpp = malloc(4);
	p->size = malloc(4);
	p->endian = malloc(4);
	p->inc_dec = 1;
	p->cam_slct = 0;
	p->light_slct = 0;
	p->curr_light = NULL;
}
