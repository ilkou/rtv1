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
