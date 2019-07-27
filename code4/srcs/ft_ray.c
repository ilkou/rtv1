/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:53:02 by oouklich          #+#    #+#             */
/*   Updated: 2019/07/13 17:54:36 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

t_ray	ft_ray(t_vector a, t_vector b)
{
	t_ray	r;

	r.A = a;
	r.B = b;
	return (r);
}

t_vector	ft_ray_function(t_ray r, double t)
{
	return (ft_add(r.A, ft_pro_d(r.B, t))); //A+t*B
}

int         ft_hit_sphere(t_sphere *s, t_ray *r, t_interval t, t_hit *rec)
{
    t_vector    oc;
    double      delta[4];
    double      result;

    oc = ft_diff(r->A, s->center);
    delta[0] = ft_dot(r->B, r->B);
    delta[1] = ft_dot(oc, r->B);
    delta[2] = ft_dot(oc ,oc) - (s->ray * s->ray);
    delta[3] = delta[1] * delta[1] - delta[0] * delta[2];
    if (delta[3] > 0)
    {
        result = (-delta[1] - sqrt(delta[3])) / delta[0];
        if (result < t.t_max && result > t.t_min)
        {
            rec->t = result;
            rec->p = ft_ray_function(*r, rec->t);
            rec->normal = ft_div_d(ft_diff(rec->p, s->center), s->ray);
            return (1);
        }
        result = (-delta[1] + sqrt(delta[3])) / delta[0];
        if (result < t.t_max && result > t.t_min)
        {
            rec->t = result;
            rec->p = ft_ray_function(*r, rec->t);
            rec->normal = ft_div_d(ft_diff(rec->p, s->center), s->ray);
            return (1);
        }
    }
    return (0);
}

int         ft_hit(t_objects *obj, t_ray *r, t_interval t, t_hit *rec)
{
    int         hit_anything = 0;
    double      closest_so_far = t.t_max;
    int         i = -1;
    t_objects    *tmp = obj;
    while (++i < obj->nbr_obj)
    {
        if (ft_hit_sphere(tmp->s, r, ft_interval(t.t_min, closest_so_far), rec))
        {
            hit_anything = 1;
            closest_so_far = rec->t;
        }
        tmp = obj->next;
    }
    return (hit_anything);
}