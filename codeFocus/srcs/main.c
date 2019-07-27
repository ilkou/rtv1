/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 22:37:07 by oouklich          #+#    #+#             */
/*   Updated: 2019/03/22 20:11:24 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"
#include <stdio.h> //delete me assi tbi
int		main(int argc, char **argv)
{
	t_ptr *p;

	if (argc != 2)
		ft_putstr("RTFM!\n");
	p = (struct s_ptr*)malloc(sizeof(struct s_ptr));
	ft_init(p, argv);
	ft_create_window(p);
	ft_create_image(p);
	ft_background(p);
    ft_cadre(p);
    ft_draw(p);
	mlx_hook(p->win, 2, 0, ft_deal_key, p);
	mlx_hook(p->win, 4, 0, ft_mouse_press, p);
	mlx_hook(p->win, 6, 0, ft_mouse_move, p);
	mlx_loop(p->mlx);
	return (0);
}

/*
 * t_vector v = ft_vector(1, 2, 3);
 * t_vector w = ft_vector(4, 5, 6);
 * t_ray r = ft_ray(v ,w);
 * printf("%f %f %f %f %f %f\n", r.A.v1, r.A.v2, r.A.v3, r.B.v1, r.B.v2, r.B.v3);
*/