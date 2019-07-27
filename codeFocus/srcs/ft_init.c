/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:02:31 by oouklich          #+#    #+#             */
/*   Updated: 2019/04/17 19:17:28 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

void	ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH
			&& y >= 0 && y < WIN_HEIGHT)
	{
		p->data[y * (int)WIN_WIDTH + x] = color;
	}
}

void	ft_create_window(t_ptr *p)
{
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HEIGHT, "rtv1");
}

void	ft_create_image(t_ptr *p)
{
	p->img = mlx_new_image(p->mlx, WIN_WIDTH, WIN_HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, p->bpp, p->size, p->endian);
}

t_camera    ft_init_camera(t_vector lookfrom, t_vector lookat, t_vector vup, double vfov)
{
    t_camera    c;
    double		aperture = 2.0;
    double		focus_dist = ft_length(ft_diff(lookfrom, lookat));

    c.lens_radius = aperture / 2;
    c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
    c.half_w = (WIN_WIDTH / WIN_HEIGHT) * c.half_h;
    c.origin = lookfrom;
    c.w = ft_to_uv(ft_diff(lookfrom, lookat));
    c.u = ft_to_uv(ft_cross(vup, c.w));
    c.v = ft_cross(c.w, c.u);
    c.lower_left_corner = ft_diff(c.origin, ft_add(ft_pro_d(c.v, focus_dist * c.half_h), ft_pro_d(c.u, focus_dist * c.half_w)));
    c.lower_left_corner = ft_diff(c.lower_left_corner, ft_pro_d(c.w, focus_dist));
    c.horizontal = ft_pro_d(c.u, 2.0 * focus_dist * c.half_w);
    c.vertical =  ft_pro_d(c.v, 2.0 * focus_dist * c.half_h);
    c.fov = vfov;
    return (c);
}

void	ft_init(t_ptr *p, char **argv)
{
	p->img = NULL;
	p->mlx = NULL;
	p->data = NULL;
	p->win = NULL;
	p->bpp = malloc(4);
	p->size = malloc(4);
	p->endian = malloc(4);
    p->antia = 2.0;
	p->fuzz = 0.3;
    p->cc = -1.0;
	p->stop = 0;
	p->color = 0;
    p->cam.fov = 20.0;
	p->cam = ft_init_camera((t_vector){3, 3, 2}, (t_vector){0, 0, -1}, (t_vector){0, 1, 0}, p->cam.fov);
    p->center = ft_vector(0, 0, -1);
}
