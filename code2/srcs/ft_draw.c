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

	p.y = rgb % 16;
	p.x = (rgb / 16) % 16;
	return (p);
}

int hex_to_int(t_point r, t_point g, t_point b)
{
	return ((int)r.x * 16 * 16 * 16 * 16 * 16 + (int)r.y * 16 * 16 * 16 * 16 +
	(int)g.x * 16 * 16 * 16 + (int)g.y * 16 * 16 + (int)b.x * 16 + (int)b.y);
}

t_vector    ft_color(t_ray r)
{
    t_vector    unit;
    double      k;

    unit = ft_to_unit_vector(r.B);
    k = 0.5 * (unit.v2 + 1.0);
    return (ft_add(ft_pro_d(ft_vector(1, 1, 1), (1.0 - k)),
                   ft_pro_d(ft_vector(0.5, 0.7, 1), k)));
}

void            ft_cadre(t_ptr *p)
{
    double	iteration;
    int		col;
    int		row;

    row = -1;
    while (++row < WIN_HEIGHT)
    {
        col = -1;
        while (++col < WIN_WIDTH)
        {
            float u = (double)col / WIN_WIDTH;
            float v = (double)row / WIN_HEIGHT;
            t_ray r = ft_ray(p->origin, ft_add(p->lower_left_corner,
                    ft_add(ft_pro_d(p->horizontal, u), ft_pro_d(p->vertical, v))));
            t_vector c = ft_color(r);
            t_vector w = ft_vector((double)col / WIN_WIDTH, (double)row / WIN_HEIGHT, 0.2);
            if ((row < FRAME || (row > WIN_HEIGHT - FRAME && row < WIN_HEIGHT))
                || (col < FRAME || (col > WIN_WIDTH - FRAME && col < WIN_WIDTH)))
                ft_mlx_putpixel(p, col, row, hex_to_int(rgb_to_hex((int)(255.99 * w.v1)),
                        rgb_to_hex((int)(255.99 * w.v2)), rgb_to_hex((int)(255.99 * w.v3))));
            else
                ft_mlx_putpixel(p, col, row, hex_to_int(rgb_to_hex((int)(255.99 * c.v1)),
                        rgb_to_hex((int)(255.99 * c.v2)), rgb_to_hex((int)(255.99 * c.v3))));
        }
    }
}

void			*ft_calcul(t_thread *p)
{
    double	iteration;
    int		col;
    int		row;

    row = -1;
    while (++row < WIN_HEIGHT)
    {
        col = (int)(p->i * WIN_WIDTH / NBTHREAD) - 1;
        while (++col < (int)((p->i + 1) * WIN_WIDTH / NBTHREAD))
        {
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
    ft_cadre(p);
	ft_begin(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}
