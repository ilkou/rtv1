/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:04:46 by oouklich          #+#    #+#             */
/*   Updated: 2019/03/22 22:22:08 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

t_point rgb_to_hex(int rgb)
{
	t_point p;

	p.x = rgb % 16;
	p.y = (rgb / 16) % 16;
	//swap p.x and p.y
	return (p);
}

int hex_to_int(t_point r, t_point g, t_point b)
{
	return ((int)r.x*16*16*16*16*16+(int)r.y*16*16*16*16+(int)g.x*16*16*16+(int)g.y*16*16+(int)b.x*16+(int)b.y);
}

void			*ft_calcul(t_thread *p)
{
	double	iteration;
	int		col;
	int		row;
	t_color	c;

	row = -1;
	while (++row < WIN_HEIGHT)
	{
		col = (int)(p->i * WIN_WIDTH / NBTHREAD) - 1;
		while (++col < (int)((p->i + 1) * WIN_WIDTH / NBTHREAD))
		{
			float r = (float)row / WIN_HEIGHT;
			float g = (float)col / WIN_WIDTH;
			float b = 0.2;
			t_point ir = rgb_to_hex((int)(255.99*r));
			t_point ig = rgb_to_hex((int)(255.99*g));
			t_point ib = rgb_to_hex((int)(255.99*b));
			ft_mlx_putpixel(p->e, col, row, hex_to_int(ir, ig, ib));
		}
	}
	pthread_exit(NULL);
}

void			ft_begin(t_ptr *p)
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].e = p;
		div[i].i = i;
		pthread_create(&thread[i], NULL, (void*)ft_calcul, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
}

void			ft_draw(t_ptr *p)
{
	ft_bzero(p->data, WIN_WIDTH * WIN_HEIGHT * 4);
	ft_begin(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}
