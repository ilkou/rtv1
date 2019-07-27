/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:36:10 by oouklich          #+#    #+#             */
/*   Updated: 2019/07/13 17:36:54 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

double	ft_length(t_vector a)
{
	return (sqrt(a.v1 * a.v1 + a.v2 * a.v2 + a.v3 * a.v3));
}

double	ft_lengthsquared(t_vector a)
{
	return (a.v1 * a.v1 + a.v2 * a.v2 + a.v3 * a.v3);
}

