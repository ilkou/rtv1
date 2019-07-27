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

t_sphere	ft_sphere(t_vector c, double r, t_vector v)
{
	t_sphere	s;

	s.center = c;
	s.ray = r;
	s.lamb = v;
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
	t_camera cam;

	cam.origin = a;
	cam.lower_left_corner = b;
	cam.horizontal = c;
	cam.vertical = d;
	return (cam);
}