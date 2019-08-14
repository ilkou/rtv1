/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 17:03:13 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/03 17:05:05 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

t_color		ft_add_c(t_color a, t_color b)
{
	return (COL(a.r + b.r, a.g + b.g, a.b + b.b));
}

t_color		ft_pro_c(t_color a, t_color b)
{
    return (COL(a.r * b.r, a.g * b.g, a.b * b.b));
}

t_color		ft_add_kc(t_color a, double k)
{
    return (COL(a.r + k, a.g + k, a.b + k));
}

t_color     ft_div_kc(t_color a, double k)
{
    return (COL(a.r / k, a.g / k, a.b / k));
}

t_color     ft_pro_kc(t_color a, double k)
{
    return (COL(a.r * k, a.g * k, a.b * k));
}

int         ft_from_rgb(int x, int y, int z)
{
    t_point r;
    t_point g;
    t_point b;

    r.y = x % 16;
    r.x = (x / 16) % 16;
    g.y = y % 16;
    g.x = (y / 16) % 16;
    b.y = z % 16;
    b.x = (z / 16) % 16;
    return ((int)r.x * 16 * 16 * 16 * 16 * 16 + (int)r.y * 16 * 16 * 16 * 16 +
            (int)g.x * 16 * 16 * 16 + (int)g.y * 16 * 16 + (int)b.x * 16 + (int)b.y);
}