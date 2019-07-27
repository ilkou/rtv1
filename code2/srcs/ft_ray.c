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