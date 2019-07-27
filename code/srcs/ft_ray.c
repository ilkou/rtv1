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

t_vector	ft_ray_function(t_ray *r, double t)
{
	return (ft_add(r->A, ft_pro_d(r->B, t))); //A+t*B
}

double      ffmin(double a, double b)
{
    return (a < b ? a : b);
}

double      ffmax(double a, double b)
{
    return (a > b ? a : b);
}

/*int         ft_hit_aabb(t_aabb *a, t_ray *r, t_interval t)
{
    t_interval  tmp;
    int     i;

    i = -1;
    while (++i < 3)
    {
        tmp.t_min = ffmin((idx(a->min, i) - idx(r->A, i)) / idx(r->B, i),
                (idx(a->max, i) - idx(r->A, i)) / idx(r->B, i));
        tmp.t_max = ffmax((idx(a->min, i) - idx(r->A, i)) / idx(r->B, i),
                (idx(a->max, i) - idx(r->A, i)) / idx(r->B, i));
        t.t_min = ffmax(tmp.t_min, t.t_min);
        t.t_max = ffmin(tmp.t_max, t.t_max);
        if (t.t_max <= t.t_min)
            return (0);
    }
    return (1);
}*/

int         ft_hit_sphere(t_objects *o, t_ray *r, t_interval t, t_hit *rec)
{
    t_vector    oc;
    double      coef[3];
    double      delta;
    double      result;

    oc = ft_diff(r->A, o->s.center);
    coef[0] = ft_dot(r->B, r->B);
    coef[1] = ft_dot(oc, r->B);
    coef[2] = ft_dot(oc ,oc) - (o->s.ray * o->s.ray);
    delta = coef[1] * coef[1] - coef[0] * coef[2];
    if (delta > 0)
    {
        result = (-coef[1] - sqrt(delta)) / coef[0];
        if (result < t.t_max && result > t.t_min)
        {
            rec->t = result;
            rec->p = ft_ray_function(r, rec->t);
            rec->normal = ft_div_d(ft_diff(rec->p, o->s.center), o->s.ray);
            return (1);
        }
        result = (-coef[1] + sqrt(delta)) / coef[0];
        if (result < t.t_max && result > t.t_min)
        {
            rec->t = result;
            rec->p = ft_ray_function(r, rec->t);
            rec->normal = ft_div_d(ft_diff(rec->p, o->s.center), o->s.ray);
            return (1);
        }
    }
    return (0);
}

int         ft_hit_xyrect(t_objects *o, t_ray *r, t_interval t, t_hit *rec)
{
    double  hit_rect;
    double  x;
    double  y;

    hit_rect = (o->box.xyrect.k - r->A.v3) / r->B.v3;
    if (hit_rect < t.t_min || hit_rect > t.t_max)
        return (0);
    x = r->A.v1 + hit_rect * r->B.v1;
    y = r->A.v2 + hit_rect * r->B.v2;
    if (x < o->box.xyrect.x0 || x > o->box.xyrect.x1 || y < o->box.xyrect.y0 || y > o->box.xyrect.y1)
        return (0);
    rec->u = (x - o->box.xyrect.x0) / (o->box.xyrect.x1 - o->box.xyrect.x0);
    rec->v = (y - o->box.xyrect.y0) / (o->box.xyrect.y1 - o->box.xyrect.y0);
    rec->t = hit_rect;
    rec->material = o->box.xyrect.mp;
    rec->p = ft_ray_function(r, hit_rect);
    rec->normal = ft_vector(0,0,1);
    return (1);
}

int         ft_hit(t_objects *obj, t_ray r, t_interval t, t_hit *rec)
{
    int         hit_anything;
    double      closest_so_far;
    t_objects    *tmp;
    int i;

    tmp = obj;
    i = 0;
    hit_anything = 0;
    closest_so_far = t.t_max;
    while (i < obj[0].nbr_obj)
    {
        if (tmp[i].hit(&tmp[i], &r, ft_interval(t.t_min, closest_so_far), rec))
        {
            hit_anything = 1;
            closest_so_far = rec->t;
            if (i == 0)
                (*rec).material = V(-500, -500, -500);
            else if (i != obj[0].nbr_obj - 1)
                (*rec).material = (tmp[i].s.ref_idx == DEFAULT) ? tmp[i].s.lamb : (t_vector){tmp[i].s.ref_idx, 0, 0};
            (*rec).type = tmp[i].s.type;
        }
        i++;
    }
    return (hit_anything);
}

t_ray   ft_get_ray(t_camera *p, double u, double v)
{
    u = (double)(u + myrand48()) / WIN_WIDTH;
    v = (double)(v + myrand48()) / WIN_HEIGHT;
    return (ft_ray(p->origin, ft_diff(ft_add(p->lower_left_corner,
            ft_add(ft_pro_d(p->horizontal, u), ft_pro_d(p->vertical, v))), p->origin)));
}
//it's a direction so don't forget to normalize 
/*t_ray   ft_get_ray(t_camera *p, double u, double v)
{
    u = (double)(u + myrand48()) / WIN_WIDTH;
    v = (double)(v + myrand48()) / WIN_HEIGHT;
    return (ft_ray(p->origin, ft_to_uv(ft_diff(ft_add(p->lower_left_corner,
                                                      ft_add(ft_pro_d(p->horizontal, u), ft_pro_d(p->vertical, v))), p->origin))));
}*/