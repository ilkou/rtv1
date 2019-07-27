/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_constructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 20:52:56 by oouklich          #+#    #+#             */
/*   Updated: 2019/07/14 20:54:28 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

t_point		ft_point(int a, int b)
{
	t_point		p;

	p.x = a;
	p.y = b;
	return (p);
}

t_sphere	ft_sphere(t_vector c, double r, t_vector v)
{
	t_sphere	s;

	s.center = c;
	s.ray = r;
	s.lamb = v;
	s.ref_idx = DEFAULT_RI;
	return (s);
}

t_sphere    ft_sphere_dielec(t_vector c, double r, double ri)
{
    t_sphere	s;

    s.center = c;
    s.ray = r;
    s.lamb = ft_vector(DEFAULT_RI, DEFAULT_RI, DEFAULT_RI);
    s.ref_idx = ri;
    return (s);
}

t_sphere    ft_sphere_texture(t_vector c, double r, t_texture txtr)
{
    t_sphere	s;

    s.center = c;
    s.ray = r;
    s.lamb = ft_vector(DEFAULT_RI, DEFAULT_RI, DEFAULT_RI);
    s.t = txtr;
    s.ref_idx = DEFAULT_RI;
    return (s);
}

t_interval	ft_interval(double a, double b)
{
	t_interval t;

	t.t_min = a;
	t.t_max = b;
	return (t);
}

t_hit       ft_rec(t_vector n, t_vector p, double t)
{
    t_hit   ret;

    ret.normal = n;
    ret.p = p;
    ret.t = t;
    return (ret);
}

t_camera	ft_camera(t_vector a, t_vector b, t_vector c, t_vector d)
{
	t_camera    cam;

	cam.origin = a;
	cam.lower_left_corner = b;
	cam.horizontal = c;
	cam.vertical = d;
	return (cam);
}

t_texture   ft_texture(double a, double b, int *d)
{
    t_texture   t;

    t.nx = a;
    t.ny = b;
    t.data = d;
    return (t);
}