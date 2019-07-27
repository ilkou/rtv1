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
int			ft_draw(t_ptr *p);
int				ft_deal_key(int key, t_ptr *p);
int				ft_mouse_press(int button, int x, int y, t_ptr *p);
int				ft_mouse_move(int x, int y, t_ptr *p);
void			ft_mlx_putpixel(t_ptr *p, int x, int y, int color);
void			ft_create_window(t_ptr *p);
void			ft_create_image(t_ptr *p);
void			ft_init(t_ptr *p, char **argv);
void            ft_cadre(t_ptr *p);
void            ft_background(t_ptr *p);

t_point		ft_point(int a, int b);
t_vector	ft_vector(double x, double y, double z);
t_vector	ft_add(t_vector a, t_vector b);
t_vector	ft_diff(t_vector a, t_vector b);
t_vector	ft_div(t_vector a, t_vector b);
t_vector	ft_pro(t_vector a, t_vector b);
t_vector	ft_to_uv(t_vector a);
t_vector	ft_pro_d(t_vector a, double k);
t_vector	ft_div_d(t_vector a, double k);
double		ft_dot(t_vector a, t_vector b);
t_vector	ft_cross(t_vector a, t_vector b);
double      ft_length(t_vector a);
double      ft_lengthsquared(t_vector a);
t_ray       ft_ray(t_vector a, t_vector b);
t_vector	ft_ray_function(t_ray *r, double t);
int         ft_hit_sphere(t_sphere *s, t_ray *r, t_interval t, t_hit *rec);
int         ft_hit(t_objects *obj, t_ray *r, t_interval t, t_hit *rec);
t_interval	ft_interval(double a, double b);
t_sphere	ft_sphere(t_vector c, double r, t_vector v);
t_sphere    ft_sphere_dielec(t_vector c, double r, double ri);
t_hit       ft_rec(t_vector n, t_vector p, double t);
t_camera	ft_camera(t_vector a, t_vector b, t_vector c, t_vector d);
t_ray       ft_get_ray(t_camera *p, double u, double v);
t_camera    ft_init_camera(t_vector lookfrom, t_vector lookat, t_vector vup, double vfov);
t_vector    ft_rand_in_unit_disk();
t_vector    ft_rand_in_unit_sphere();

#endif
