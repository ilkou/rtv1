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

void	ft_init(t_ptr **p, char **argv)
{
	*p = (struct s_ptr*)malloc(sizeof(struct s_ptr));
	(*p)->img = NULL;
	(*p)->mlx = NULL;
	(*p)->data = NULL;
	(*p)->win = NULL;
	(*p)->bpp = malloc(4);
	(*p)->size = malloc(4);
	(*p)->endian = malloc(4);
    (*p)->antia = 15.0;
    (*p)->cc = -1.0;
	(*p)->stop = 0;
	(*p)->color = 0;
	(*p)->cam = ft_camera(ft_vector(0, 0, 0), ft_vector(-2.0, -1.0, -1.0),
			ft_vector(4.0, 0, 0), ft_vector(0, 2.0, 0));
    (*p)->center = ft_vector(0, 0, -1);
}
