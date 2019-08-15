/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:04:46 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 18:03:06 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

t_color		ft_raytrace_color(t_scene *s, t_ray *r, t_object *o)
{
	t_color		color;

	color = COL(0.0, 0.0, 0.0);
	if (ft_hit(o, *r, I(0.0001, DBL_MAX), &s->record))
		ft_lighting(s, s->light, &color);
	ft_adjustment(&color);
	return (color);
}

t_color		ft_ray_tracer(t_scene *scene, int col, int row)
{
	t_color		c;
	t_ray		r;
	int			ss;

	c = COL(0, 0, 0);
	ss = -1;
	while (++ss < (int)scene->anti_a)
	{
		r = ft_get_ray(&scene->cam, col, row);
		c = ft_add_c(c, ft_raytrace_color(scene, &r, scene->object));
	}
	c = ft_div_kc(c, scene->anti_a);
	return (c);
}

void		*ft_calcul(t_thread *p)
{
	t_color		c;
	int			color;
	int			col;
	int			row;

	row = IMG_HEIGHT + 1;
	while (--row >= 0)
	{
		col = (int)(p->i * IMG_WIDTH / NBTHREAD) - 1;
		while (++col < (int)((p->i + 1) * IMG_WIDTH / NBTHREAD))
		{
			c = ft_ray_tracer(p->scene, col, row);
			color = ft_from_rgb(RGB(c.r), RGB(c.g), RGB(c.b));
			ft_mlx_putpixel(p->e, col, IMG_HEIGHT - row, color);
		}
	}
	ft_free_objects(p->scene->object);
	ft_free_lights(p->scene->light);
	free(p->scene);
	pthread_exit(NULL);
}

void		ft_begin(t_ptr *p)
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].e = p;
		div[i].i = i;
		div[i].scene = ft_copy_scene(p->scene);
		pthread_create(&thread[i], NULL, (void*)ft_calcul, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
}

int			ft_draw(t_ptr *p)
{
	ft_bzero(p->data, IMG_WIDTH * IMG_HEIGHT * 4);
	ft_background(p);
	ft_begin(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, FRAME, MENU_BAR);
	return (1);
}
