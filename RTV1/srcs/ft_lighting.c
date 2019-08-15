/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:41:21 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 17:47:29 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

t_vector	ft_reflect(t_vector v, t_vector n)
{
	return (ft_sub(v, ft_pro_k(ft_pro_k(n, 2), ft_dot(v, n))));
}

void		ft_adjustment(t_color *c)
{
	c->r = ft_clamping(c->r);
	c->g = ft_clamping(c->g);
	c->b = ft_clamping(c->b);
}

int			ft_shading(t_scene *scene, t_light *light)
{
	t_ray		r;
	t_hit		rec;
	t_object	*obj;
	double		closest_so_far;

	obj = scene->object;
	r.dir = ft_sub(light->pos, scene->record.p);
	closest_so_far = sqrtf(ft_dot(r.dir, r.dir));
	r.origin = scene->record.p;
	r.dir = ft_normalize(r.dir);
	while (obj != NULL)
	{
		if (obj != scene->record.curr_obj)
			if (ft_hit(obj, r, I(0.0001, closest_so_far), &rec))
				return (1);
		obj = obj->next;
	}
	return (0);
}

double		ft_specularity(t_scene *s, t_vector light_vec, double fd)
{
	t_vector	reflected;
	double		spec;
	double		n_dot_l;

	spec = 0.0;
	light_vec = ft_normalize(light_vec);
	reflected = ft_reflect(light_vec, s->record.n);
	n_dot_l = ft_dot(reflected, s->record.ray.dir);
	if (n_dot_l > 0.0)
		spec = pow(n_dot_l, s->shininess) * s->pd * fd;
	return (ft_clamping(spec));
}

void		ft_lighting(t_scene *s, t_light *l, t_color *col)
{
	t_vector	light_vec;
	t_object	obj;
	double		coef;
	double		fd;

	obj = *s->record.curr_obj;
	if (!l)
		*col = ft_pro_kc(obj.col, 0.15);
	while (l != NULL)
	{
		coef = l->intensity;
		light_vec = ft_sub(l->pos, s->record.p);
		if (!ft_shading(s, l))
			coef += ft_clamping(ft_dot(ft_normalize(light_vec), s->record.n));
		fd = ft_clamping(1.0 / (0.02 * ft_length(light_vec)));
		coef = ft_clamping(coef * s->pd * fd);
		*col = ft_add_c(*col, ft_pro_kc(ft_pro_c(obj.col, l->col), coef));
		if (!ft_shading(s, l) && s->spec)
			*col = ft_add_kc(*col, ft_specularity(s, light_vec, fd));
		l = l->next;
	}
}
