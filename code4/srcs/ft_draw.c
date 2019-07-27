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

double  hit_sphere(t_vector a, double ray, t_ray r)
{
    t_vector    oc;
    double      delta[4];

    oc = ft_diff(r.A, a);
    delta[0] = ft_dot(r.B, r.B);
    delta[1] = 2.0 * ft_dot(oc, r.B);
    delta[2] = ft_dot(oc ,oc) - (ray * ray);
    delta[3] = delta[1] * delta[1] - 4 * delta[0] * delta[2];
    if (delta[3] < 0)
        return (-1.0);
    else
        return (-delta[1] - sqrt(delta[3]) / (2.0 * delta[0]));
}
/*double      t;

    t = hit_sphere(p->center, 0.5, r);
    if (t > 0.0)
    {
        t_vector N = ft_to_unit_vector(ft_diff(ft_ray_function(r, t), ft_vector(0,0,-1)));
        return (ft_pro_d(ft_vector(N.v1+1, N.v2+1, N.v3+1), 0.5));
    }*/
t_vector    ft_color(t_ray r, t_ptr *p, t_objects *o)
{
    t_vector    unit;
    double      k;
    t_hit       rec;
    //rec = ft_rec(ft_vector(0,0,0), ft_vector(0,0,0), 0);
    if (ft_hit(o, &r, ft_interval(0.0, DBL_MAX), &rec))
        return (ft_pro_d(ft_vector(rec.normal.v1 + 1, rec.normal.v2 + 1,rec.normal.v3 + 1), 0.5));
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
    t_objects obj;
    t_objects obj2;
    t_sphere    s1 = ft_sphere(ft_vector(0,0,-1), 0.5);
    t_sphere    s2 = ft_sphere(ft_vector(0,-100.5,-1), 100);
    obj.s = &s1;
    obj2.s = &s2;
    obj.next = &obj2;
    obj2.next = NULL;
    obj.nbr_obj = 2;
    obj2.nbr_obj = 2;
    row = WIN_HEIGHT + 1;
    while (--row >= 0)
    {
        col = -1;
        while (++col < WIN_WIDTH)
        {
            float u = (double)col / WIN_WIDTH;
            float v = (double)row / WIN_HEIGHT;
            t_ray r = ft_ray(p->origin, ft_add(p->lower_left_corner,
                    ft_add(ft_pro_d(p->horizontal, u), ft_pro_d(p->vertical, v))));
            t_vector c = ft_color(r, p, &obj);
            t_vector w = ft_vector((double)col / WIN_WIDTH, (double)row / WIN_HEIGHT, 0.2);
            if ((row < FRAME || (row > WIN_HEIGHT - FRAME && row < WIN_HEIGHT))
                || (col < FRAME || (col > WIN_WIDTH - FRAME && col < WIN_WIDTH)))
                ft_mlx_putpixel(p, col, row, hex_to_int(rgb_to_hex((int)(255.99 * w.v1)),
                        rgb_to_hex((int)(255.99 * w.v2)), rgb_to_hex((int)(255.99 * w.v3))));
            else
                ft_mlx_putpixel(p, col, WIN_HEIGHT - row, hex_to_int(rgb_to_hex((int)(255.99 * c.v1)),
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
