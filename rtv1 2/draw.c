/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 22:40:53 by mel-jadi          #+#    #+#             */
/*   Updated: 2019/04/18 00:09:07 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_fzero(float *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		s[i] = 0.0;
		i++;
	}
}

double	ft_inter_sphere(t_th *p, t_obj *tmp, t_vec ray, t_vec pos)
{
	double disc;

	p->dist = ft_vectorsub(&pos, &tmp->pos);
	p->a = ft_vectordot(&ray, &ray);
	p->b = 2 * ft_vectordot(&ray, &p->dist);
	p->c = ft_vectordot(&p->dist, &p->dist) - (tmp->size * tmp->size);
	disc = p->b * p->b - 4 * p->a * p->c;
	if (disc < 0)
		return (-1);
	p->t0 = (-p->b + sqrtf(disc)) / (2 * p->a);
	p->t1 = (-p->b - sqrtf(disc)) / (2 * p->a);
	if (p->t0 > p->t1)
		p->t0 = p->t1;
	return (p->t0);
}

t_obj	*ft_intersection(t_th *p, t_obj *node, t_vec ray, t_vec pos)
{
	t_obj	*tmp;
	double	dist;

	tmp = NULL;
	p->t = 80000.0;
	while (node != NULL)
	{
		if (node->type == 1)
		{
			//dist = ft_inter_cone(p, node, ray, pos);
		}
		else if (node->type == 2)
		{
			//dist = ft_inter_cylinder(p, node, ray, pos);
		}
		else if (node->type == 3)
		{
			//dist = ft_inter_plane(p, node, ray, pos);
        }
		else if (node->type == 4)
			dist = ft_inter_sphere(p, node, ray, pos);
		if (dist > 0.0001 && dist < p->t)
		{
			tmp = node;
			p->t = dist;
		}
		node = node->next;
	}
	return (tmp);
}

float	*ft_set_ray(t_th *p, float *tab, double x, double y)
{
	double	u;
	double	v;

	u = (IMG_WIDTH - (double)x * 2.0) / IMG_HEIGHT;
	v = (IMG_HEIGHT - (double)y * 2.0) / IMG_WIDTH;
	p->k = ft_vectorsub(&p->cam_dir, &p->cam_pos);
	ft_vectornorm(&p->k);
	p->i = ft_vectorcross(&p->k, &(t_vec){0.0, 1.0, 0.0});
	ft_vectornorm(&p->i);
	p->j = ft_vectorcross(&p->i, &p->k);
	p->ray_dir = (t_vec){u * p->i.x + v * p->j.x + FOV * p->k.x, u * p->i.y + v * p->j.y
		+ FOV * p->k.y, u * p->i.z + v * p->j.z + FOV * p->k.z};
	ft_vectornorm(&p->ray_dir);
	p->cpt = 0;
	ft_fzero(tab, 4);
	return (tab);
}

float	ft_spec(t_th *p, t_vec dist, float d, float lambert)
{
	float	spec;
	float	tmp;
	t_vec	ref;

	spec = 0.0;
	ref = ft_vectorscale(&p->norm, (2.0 * ft_vectordot(&p->norm, &dist)));
	ref = ft_vectorsub(&dist, &ref);
	if ((tmp = ft_vectordot(&ref, &p->ray_dir)) > 0.0 && lambert > 0.15)
	{
		spec = pow(tmp, 20.0) * 4 * d;
		spec = ft_clamp(spec, 0.0, 1.0);
	}
	return (spec);
}

t_vec	ft_norm(t_th *p, t_obj *tmp, t_vec pos)
{
	t_vec	norm;
	t_vec	temp;
	t_vec	temp2;

	if (tmp->type == 1 || tmp->type == 2)
	{
		temp = ft_vectorscale(&tmp->rot,
			(ft_vectordot(&p->ray_dir, &tmp->rot) * p->t0
			+ ft_vectordot(&p->dist, &tmp->rot)));
		if (tmp->type == 1)
			temp = ft_vectorscale(&temp, (1 + pow(tan(tmp->size), 2)));
		temp2 = ft_vectorsub(&pos, &tmp->pos);
		norm = ft_vectorsub(&temp2, &temp);
	}
	else if (tmp->type == 3)
		norm = tmp->rot;
	if (tmp->type == 4)
		norm = ft_vectorsub(&pos, &tmp->pos);
	ft_vectornorm(&norm);
	return (norm);
}

int		ft_shadow(t_th *p, t_obj *tmp, t_obj *light, t_vec pos)
{
	t_obj	*node;
	t_vec	dist;

	node = p->obj;
	dist = ft_vectorsub(&light->pos, &pos);
	p->t = sqrtf(ft_vectordot(&dist, &dist));
	ft_vectornorm(&dist);
	while (node != NULL)
	{
		if (node != tmp)
		{
			if (node->type == 1)
			{
				//p->a = ft_inter_cone(p, node, dist, pos);
			}
			else if (node->type == 2)
			{
				//p->a = ft_inter_cylinder(p, node, dist, pos);
			}
			else if (node->type == 3)
			{
				//p->a = ft_inter_plane(p, node, dist, pos);
			}
			else if (node->type == 4)
				p->a = ft_inter_sphere(p, node, dist, pos);
			if (p->a > 0.0001 && p->a < p->t)
				return (1);
		}
		node = node->next;
	}
	return (0);
}

float		*ft_endlight(t_obj *tmp, t_obj *light, float *tab, float d)
{
	tab[3] = ft_clamp(tab[3] * 4.0 * d, 0.0, 1.0);
	tab[0] += tab[3] * (tmp->col.red / 255) * (light->col.red / 255);
	tab[1] += tab[3] * (tmp->col.green / 255) * (light->col.green / 255);
	tab[2] += tab[3] * (tmp->col.blue / 255) * (light->col.blue / 255);
	return (tab);
}

t_obj	*ft_ref_init(t_th *p, t_obj *tmp, t_vec *pos)
{
	t_obj	*tmp2;

	p->t = 8000.0;
	p->ref = ft_vectorscale(&p->norm,
		(2 * ft_vectordot(&p->refpos, &p->norm)));
	p->ref = ft_vectorsub(&p->refpos, &p->ref);
	ft_vectornorm(&p->ref);
	tmp2 = ft_ref_inter(p, p->obj, tmp, *pos);
	if (!tmp2)
		return (NULL);
	*pos = (t_vec){pos->x + p->t * p->ref.x, pos->y +
		p->t * p->ref.y, pos->z + p->t * p->ref.z};
	p->refpos = (t_vec){p->ref.x, p->ref.y, p->ref.z};
	p->norm = ft_norm(p, tmp2, *pos);
	return (tmp2);
}

t_obj	*ft_ref_inter(t_th *p, t_obj *node, t_obj *tmp, t_vec pos)
{
	t_obj	*tmp2;
	double	dist;

	tmp2 = NULL;
	while (node != NULL)
	{
		if (node != tmp)
		{
			if (node->type == 1)
			{
				//dist = ft_inter_cone(p, node, p->ref, pos);
			}
			else if (node->type == 2)
			{
				//dist = ft_inter_cylinder(p, node, p->ref, pos);
			}
			else if (node->type == 3)
			{
				//dist = ft_inter_plane(p, node, p->ref, pos);
			}
			else if (node->type == 4)
				dist = ft_inter_sphere(p, node, p->ref, pos);
			if (dist > 0.0001 && dist < p->t)
			{
				tmp2 = node;
				p->t = dist;
			}
		}
		node = node->next;
	}
	return (tmp2);
}

float    *ft_reflect(t_th *p, t_obj *tmp, t_vec *pos, float *tab)
{
    t_obj    *tmp2;
    t_obj    *light;
    t_vec    dist;
    double    d;
    
    if (p->cpt >= p->maxref || (light = p->light) == NULL)
        return (tab);
    if ((tmp2 = ft_ref_init(p, tmp, pos)) == NULL || (p->cpt++) < 0)
        return (tab);
    while (light != NULL)
    {
        tab[3] = 0.14;
        dist = ft_vectorsub(&light->pos, pos);
        d = ft_clamp(1.0 / sqrtf(sqrtf(ft_vectordot(&dist, &dist))), 0.0, 1.0);
        ft_vectornorm(&dist);
        if (ft_shadow(p, tmp2, light, *pos) == 0)
            tab[3] += ft_clamp(ft_vectordot(&dist, &p->norm), 0.0, 1.0);
        tab = ft_endlight(tmp2, light, tab, d);
        tab[0] += (p->spec == 1 && tmp2->type != 3) ? ft_spec(p, dist, d, tab[3]) : 0.0;
        tab[1] += (p->spec == 1 && tmp2->type != 3) ? ft_spec(p, dist, d, tab[3]) : 0.0;
        tab[2] += (p->spec == 1 && tmp2->type != 3) ? ft_spec(p, dist, d, tab[3]) : 0.0;
        light = light->next;
    }
    return ((p->pref == 1 && tmp2->type != 3) ? tab : ft_reflect(p, tmp2, pos, tab));
}

float			*ft_lambert(t_th *p, t_obj *tmp, t_obj *light, float *tab)
{
	t_vec	pos;
	t_vec	dist;
	float	d;

	pos = (t_vec){p->cam_pos.x + p->t * p->ray_dir.x, p->cam_pos.y +
		p->t * p->ray_dir.y, p->cam_pos.z + p->t * p->ray_dir.z};
	p->norm = ft_norm(p, tmp, pos);
	while (light != NULL)
	{
		tab[3] = 0.15;
		dist = ft_vectorsub(&light->pos, &pos);
		d = ft_clamp((1.0 / sqrtf(sqrtf(ft_vectordot(&dist, &dist)))), 0., 1.);
		ft_vectornorm(&dist);
		if (ft_shadow(p, tmp, light, pos) == 0)
			tab[3] += ft_clamp(ft_vectordot(&dist, &p->norm), 0.0, 1.0);
		tab = ft_endlight(tmp, light, tab, d);
		tab[0] += (p->spec == 1 && tmp->type != 3) ? ft_spec(p, dist, d, tab[3]) : 0.0;
		tab[1] += (p->spec == 1 && tmp->type != 3) ? ft_spec(p, dist, d, tab[3]) : 0.0;
		tab[2] += (p->spec == 1 && tmp->type != 3) ? ft_spec(p, dist, d, tab[3]) : 0.0;
		light = light->next;
	}
	p->refpos = (t_vec){p->ray_dir.x, p->ray_dir.y, p->ray_dir.z};
	return ((p->pref == 1 && tmp->type != 3) ? tab : ft_reflect(p, tmp, &pos, tab));
}

int		ft_raytrace(t_th *p, t_obj *node, double x, double y)
{
	t_obj	*tmp;
	float	*tab;
	float	r[3];
	double	f;

	if (!(tab = (float *)malloc(sizeof(float) * 4)))
		return (-1);
	ft_fzero(r, 3);
	f = 0.0;
	while (y < p->ty + 1 && (x = p->tx) > -1)
	{
		while (x < p->tx + 1 && (f += 1) > 0)
		{
			ft_set_ray(p, tab, x, y);
			if ((tmp = ft_intersection(p, node, p->ray_dir, p->cam_pos)))
				tab = ft_lambert(p, tmp, p->light, tab);
			ft_average(r, tab);
			x = x + (1.0 / p->aa);
		}
		y = y + (1.0 / p->aa);
	}
	ft_mlx_putpixel(p, p->tx, p->ty, (((int)(r[0] / f * 255) & 0xff) << 16) +
		(((int)(r[1] / f * 255) & 0xff) << 8) + ((int)(r[2] / f * 255) & 0xff));
	free(tab);
	return (0);
}

void	ft_write_img(t_ptr *p)
{
	double		x;
	double		y;
	t_obj		*node;
	t_th		*th;

	node = p->obj;
	th = (t_th *)malloc(sizeof(t_th));
	ft_copy(p, th);
	y = 0.0;
	while (y < IMG_HEIGHT)
	{
		x = 0.0;
		while (x < IMG_WIDTH)
		{
			th->ty = (int)y;
			th->tx = (int)x;
            ft_raytrace(th, node, x, y);
			x++;
		}
		y++;
	}
}

void	ft_draw(t_ptr *p)
{
	ft_bzero(p->data, IMG_WIDTH * IMG_HEIGHT * 4);
	ft_write_img(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}

