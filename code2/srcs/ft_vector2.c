/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:54:32 by oouklich          #+#    #+#             */
/*   Updated: 2019/07/13 14:56:29 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

t_vector	ft_to_unit_vector(t_vector a)
{
	float k;

	k = 1.0 / sqrt(a.v1 * a.v1 + a.v2 * a.v2 + a.v3 * a.v3);
	return (ft_pro_d(a, k));
}

t_vector	ft_pro_d(t_vector a, double k)
{
	return (ft_vector(a.v1 * k, a.v2 * k, a.v3 * k));
}

t_vector	ft_div_d(t_vector a, double k)
{
	return (ft_vector(a.v1 / k, a.v2 / k, a.v3 / k));
}

double		ft_dot(t_vector a, t_vector b)
{
	return (a.v1 * b.v1 + a.v2 * b.v2 + a.v3 * b.v3);
}

t_vector	ft_cross(t_vector a, t_vector b)
{
	return (ft_vector((a.v2 * b.v3 - a.v3 * b.v2), -(a.v1 * b.v3 - a.v3 * b.v1),
			(a.v1 * b.v2 - a.v2 * b.v1)));
}