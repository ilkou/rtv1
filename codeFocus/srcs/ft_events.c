/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:06:06 by oouklich          #+#    #+#             */
/*   Updated: 2019/03/23 11:52:24 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_deal_key(int key, t_ptr *p)
{
	if (key == MLX_KEY_PAD_ESC)
	{
		mlx_destroy_image(p->mlx, p->img);
		mlx_destroy_window(p->mlx, p->win);
		free(p);
		exit(0);
	}
    /*ft_putnbr(key);
    ft_putendl("");*/
    if (key == 84)
        p->cam.origin.v2 -= 0.1;
    if (key == 91)
        p->cam.origin.v2 += 0.1;
    if (key == 86)
        p->cam.origin.v1 -= 0.1;
    if (key == 88)
        p->cam.origin.v1 += 0.1;
    if (key == 78)
        p->cam.origin.v3 -= 0.1;
    if (key == 69)
        p->cam.origin.v3 += 0.1;
    if (key == 121)
        p->cam.fov -= 5.0;
    if (key == 116)
        p->cam.fov += 5.0;
	if (key == MLX_KEY_PAD_A)
		p->antia = 100.0;
    if (key == MLX_KEY_PAD_S)
        p->antia = 5.0;
	if (key == MLX_KEY_PAD_LEFT)
	    p->cc += 0.1;
	if (key == MLX_KEY_PAD_RIGHT)
        p->cc -= 0.1;
	if (key == MLX_KEY_PAD_UP)
        p->cc += 0.1;
	if (key == MLX_KEY_PAD_DOWN)
        p->cc -= 0.1;
	p->cam = ft_init_camera(p->cam.origin, (t_vector){0, 0, -1}, (t_vector){0, 1, 0}, p->cam.fov);
    ft_draw(p);
	return (key);
}

int			ft_mouse_press(int button, int x, int y, t_ptr *p)
{
	if (button == 5)
	{

	}
	if (button == 4)
	{

	}
	ft_draw(p);
	return (0);
}

int			ft_mouse_move(int x, int y, t_ptr *p)
{
	if (0)
	{
		ft_draw(p);
	}
	return (0);
}
