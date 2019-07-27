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
void            ft_cadre(t_ptr *p);

t_vector	ft_vector(double x, double y, double z);
t_vector	ft_add(t_vector a, t_vector b);
t_vector	ft_diff(t_vector a, t_vector b);
t_vector	ft_div(t_vector a, t_vector b);
t_vector	ft_pro(t_vector a, t_vector b);
t_vector	ft_to_unit_vector(t_vector a);
t_vector	ft_pro_d(t_vector a, double k);
t_vector	ft_div_d(t_vector a, double k);
double		ft_dot(t_vector a, t_vector b);
t_vector	ft_cross(t_vector a, t_vector b);
double      ft_length(t_vector a);
double      ft_lengthsquared(t_vector a);
t_ray       ft_ray(t_vector a, t_vector b);

#endif
