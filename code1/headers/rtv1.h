/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 20:10:19 by oouklich          #+#    #+#             */
/*   Updated: 2019/07/13 12:25:31 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "rtv1_struct.h"

void			*ft_calcul(t_thread *p);
void			ft_begin(t_ptr *p);
void			ft_draw(t_ptr *p);
int				ft_deal_key(int key, t_ptr *p);
int				ft_mouse_press(int button, int x, int y, t_ptr *p);
int				ft_mouse_move(int x, int y, t_ptr *p);
void			ft_mlx_putpixel(t_ptr *p, int x, int y, int color);
void			ft_create_window(t_ptr *p);
void			ft_create_image(t_ptr *p);
void			ft_init(t_ptr **p, char **argv);

#endif
