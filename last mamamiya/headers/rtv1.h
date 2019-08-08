/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 20:10:19 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/08 21:12:45 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "rtv1_struct.h"

void			ft_debug();

double			ffmin(double a, double b);
double			ffmax(double a, double b);
void			*ft_calcul(t_thread *p);
void			ft_begin(t_ptr *p);
int				ft_draw(t_ptr *p);
int				ft_close(t_ptr *p);
int				ft_deal_key(int key, t_ptr *p);
int				ft_mouse_press(int button, int x, int y, t_ptr *p);
void			ft_mlx_putpixel(t_ptr *p, int x, int y, int color);
void			ft_create_window(t_ptr *p);
void			ft_create_image(t_ptr *p);
void			ft_init(t_ptr *p, char **argv);
void			ft_background(t_ptr *p);

int				ft_hit(t_object *obj, t_ray r, t_interval t, t_hit *h);
int				ft_hit_sphere(t_object *o, t_ray *r, t_interval t, t_hit *h);
int				ft_hit_cylinder(t_object *o, t_ray *r, t_interval t, t_hit *h);
int				ft_hit_cone(t_object *o, t_ray *r, t_interval t, t_hit *h);
int				ft_hit_plane(t_object *o, t_ray *r, t_interval t, t_hit *h);

void			ft_free_objects(t_object *obj);
void			ft_free_lights(t_light *light);
t_light			*ft_copy_lights(t_light *old);
t_object		*ft_copy_objects(t_object *old, int one_object);
t_scene			*ft_copy_scene(t_scene *old);

t_camera		ft_init_camera(t_vector lookfrom, t_vector lookat, double vfov);

t_vector		ft_vector(double x, double y, double z);
t_vector		ft_add(t_vector a, t_vector b);
t_vector		ft_sub(t_vector a, t_vector b);
t_vector		ft_div(t_vector a, t_vector b);
t_vector		ft_pro(t_vector a, t_vector b);
t_vector		ft_normalize(t_vector a);
t_vector		ft_pro_k(t_vector a, double k);
t_vector		ft_div_k(t_vector a, double k);
t_vector		ft_cross(t_vector a, t_vector b);
double			ft_dot(t_vector a, t_vector b);
double			idx(t_vector v, int i);
double			ft_length(t_vector a);
double			ft_lengthsquared(t_vector a);

t_color			ft_add_c(t_color a, t_color b);
t_color			ft_div_kc(t_color a, double k);
t_color			ft_pro_c(t_color a, t_color b);
t_color			ft_add_kc(t_color a, double k);
t_color			ft_pro_kc(t_color a, double k);
int				ft_from_rgb(int x, int y, int z);

t_ray			ft_ray(t_vector a, t_vector b);
t_ray			ft_get_ray(t_camera *p, double u, double v);
t_vector		ft_ray_function(t_ray *r, double t);
double			ffmin(double a, double b);
double			ffmax(double a, double b);

t_vector		ft_rot_x(t_vector old, double theta);
t_vector		ft_rot_y(t_vector old, double theta);
t_vector		ft_rot_z(t_vector old, double theta);

int				ft_bg_col(int bg, int x, int y);
void			ft_background(t_ptr *p);
char			*ft_ctoa(t_color c);
char			*ft_vtoa(t_vector v);
void			ft_menu_bar(t_ptr *p);

#endif
