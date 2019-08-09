/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:30:00 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/07 20:48:27 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_hit_cone(t_object *o, t_ray *r, t_interval t, t_hit *rec)
{
	rec->oc = ft_sub(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (ft_dot(r->dir, rec->oc) - (1 + pow(tan(o->size), 2))
			* ft_dot(r->dir, o->rot) * ft_dot(rec->oc, o->rot));
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(rec->oc, o->rot), 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->r[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->r[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->r[0] = rec->r[0] < rec->r[1] ? rec->r[0] : rec->r[1];
	if (rec->r[0] < t.t_max && rec->r[0] > t.t_min)
	{
		rec->t = rec->r[0];
		rec->p = ft_ray_function(r, rec->t);
		rec->temp = ft_pro_k(o->rot, (ft_dot(r->dir, o->rot) * rec->t
					+ ft_dot(rec->oc, o->rot)));
		rec->temp = ft_pro_k(rec->temp, (1 + pow(tan(o->size), 2)));
		rec->n = ft_normalize(ft_sub(ft_sub(rec->p, o->pos), rec->temp));
		return (1);
	}
	return (0);
}

int			ft_hit_cylinder(t_object *o, t_ray *r, t_interval t, t_hit *rec)
{
	rec->oc = ft_sub(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir) - pow(ft_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (ft_dot(r->dir, rec->oc) - (ft_dot(r->dir, o->rot)
				* ft_dot(rec->oc, o->rot)));
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - pow(ft_dot(rec->oc, o->rot), 2)
		- o->size * o->size;
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta >= 0)
	{
		rec->r[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->r[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->r[0] = rec->r[0] < rec->r[1] ? rec->r[0] : rec->r[1];
		if (rec->r[0] < t.t_max && rec->r[0] > t.t_min)
		{
			rec->t = rec->r[0];
			rec->p = ft_ray_function(r, rec->t);
			rec->n = ft_normalize(ft_sub(ft_sub(rec->p, o->pos),
						ft_pro_k(o->rot, ft_dot(r->dir, o->rot)
							* rec->t + ft_dot(rec->oc, o->rot))));
			return (1);
		}
	}
	return (0);
}

int			ft_hit_plane(t_object *o, t_ray *r, t_interval t, t_hit *rec)
{
	rec->t = ((ft_dot(o->rot, o->pos) - ft_dot(o->rot, r->origin))
			/ ft_dot(o->rot, r->dir));
	if (rec->t >= t.t_max || rec->t <= t.t_min)
		return (0);
	rec->n = o->rot;
	rec->p = ft_ray_function(r, rec->t);
	return (1);
}

int			ft_hit_sphere(t_object *o, t_ray *r, t_interval t, t_hit *rec)
{
	rec->oc = ft_sub(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir);
	rec->coef[1] = 2 * ft_dot(rec->oc, r->dir);
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - (o->size * o->size);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta >= 0)
	{
		rec->r[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->r[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->r[0] = rec->r[0] < rec->r[1] ? rec->r[0] : rec->r[1];
		if (rec->r[0] < t.t_max && rec->r[0] > t.t_min)
		{
			rec->t = rec->r[0];
			rec->p = ft_ray_function(r, rec->t);
			rec->n = ft_normalize(ft_sub(rec->p, o->pos));
			return (1);
		}
	}
	return (0);
}

int			ft_hit(t_object *obj, t_ray r, t_interval t, t_hit *rec)
{
	double		closest_so_far;
	int			hit_anything;

	hit_anything = 0;
	closest_so_far = t.t_max;
	while (obj)
	{
		if (obj->hit(obj, &r, I(t.t_min, closest_so_far), rec))
		{
			hit_anything = 1;
			closest_so_far = rec->t;
			rec->col = obj->col;
			rec->hit = obj->hit;
			rec->curr_obj = obj;
			rec->ray = r;
		}
		obj = obj->next;
	}
	return (hit_anything);
}
