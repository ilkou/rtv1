/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 22:26:51 by mel-jadi          #+#    #+#             */
/*   Updated: 2019/04/18 20:34:28 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		ft_deal_key(int key, t_ptr *p)
{
	if (key == MLX_KEY_PAD_ESC)
	{
		mlx_destroy_image(p->mlx, p->img);
		mlx_destroy_window(p->mlx, p->win);
		free(p);
		exit(0);
	}
	if (key == MLX_KEY_PAD_PLUS)
	{
		p->light->pos.z += 7;
	}
	if (key == MLX_KEY_PAD_MINUS)
	{
		p->light->pos.z -= 57;
	}
    if (key == 88) // 6
    {
        p->light->pos.x += 7;
    }
    if (key == 86) // 4
    {
        p->light->pos.x -= 7;
    }
    if (key == 91) // 8
    {
        p->light->pos.y += 7;
    }
    if (key == 84) // 2
    {
        p->light->pos.y -= 7;
    }
    //printf("%d\n", key);
	ft_draw(p);
	return (key);
}

int		ft_mouse_press(int button, int x, int y, t_ptr *p)
{
    x = y;
	if (button == 5)
	{
		
	}
	else if (button == 4)
	{
		
	}
	ft_draw(p);
	return (button);
}
