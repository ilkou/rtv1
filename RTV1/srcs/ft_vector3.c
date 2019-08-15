/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:36:10 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 18:36:02 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

double		idx(t_vector v, int i)
{
	if (i == 0)
		return (v.v1);
	else if (i == 1)
		return (v.v2);
	else
		return (v.v3);
}

double		ft_length(t_vector a)
{
	return (sqrt(a.v1 * a.v1 + a.v2 * a.v2 + a.v3 * a.v3));
}

double		ft_lengthsquared(t_vector a)
{
	return (a.v1 * a.v1 + a.v2 * a.v2 + a.v3 * a.v3);
}
