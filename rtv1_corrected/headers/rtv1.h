/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 20:10:19 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/17 12:38:34 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "rtv1_define.h"
# include "rtv1_struct.h"

double			ft_clamping(double value);
t_vector		ft_reflect(t_vector v, t_vector n);
void			ft_adjustment(t_color *c);
int				ft_shading(t_scene *scene, t_light *light);
double			ft_specularity(t_scene *s, t_vector light_vec, double fd);
void			ft_lighting(t_scene *s, t_light *l, t_color *col);

void			ft_add_camera(t_ptr *p, int fd, char **line, int t);
void			ft_get_object(t_ptr *p, t_object *obj, int fd, char **line);
void			ft_add_object(t_ptr *p, int fd, char **line, int t);
void			ft_add_light(t_ptr *p, int fd, char **line);
void			ft_get_data(t_ptr *p, int fd);

int				ft_check_brackets(char *s);
void			ft_do_rot(t_ptr *p, t_vector *ret, char **each);
t_vector		ft_linetorot(t_ptr *p, char **line, int free_it);
t_vector		ft_linetovec(t_ptr *p, char **line, int free_it);
t_color			ft_linetocol(t_ptr *p, char **line, int free_it);
double			ft_linetod(t_ptr *p, char **line, int free_it);
void			ft_check_data(t_ptr *p);
void			ft_parser(t_ptr *p, char *chemin);

double			ffmin(double a, double b);
double			ffmax(double a, double b);
t_color			ft_raytrace_color(t_scene *s, t_ray *r, t_object *o);
t_color			ft_ray_tracer(t_scene *scene, int col, int row);
void			*ft_calcul(t_thread *p);
void			ft_begin(t_ptr *p);
int				ft_draw(t_ptr *p);

int				ft_delete_object(t_object **list, t_object **to_delete);
void			ft_select_obj(t_ptr *p, int col, int row);
void			ft_selected_event(int key, t_ptr *p);
int				ft_menu_event(int key, t_ptr *p);

void			ft_free_exit(char *display, int err, t_ptr **p);
int				ft_close(t_ptr *p);
int				ft_deal_key(int key, t_ptr *p);
int				ft_mouse_press(int button, int x, int y, t_ptr *p);

void			ft_mlx_putpixel(t_ptr *p, int x, int y, int color);
void			ft_create_window(t_ptr *p);
void			ft_create_image(t_ptr *p);
void			ft_init(t_ptr *p);
void			ft_background(t_ptr *p);

int				ft_hit(t_object *obj, t_ray r, t_interval t, t_hit *h);
int				ft_hit_sphere(t_object *o, t_ray *r, t_interval t, t_hit *h);
int				ft_hit_cylinder(t_object *o, t_ray *r, t_interval t, t_hit *h);
int				ft_hit_cone(t_object *o, t_ray *r, t_interval t, t_hit *h);
int				ft_hit_plane(t_object *o, t_ray *r, t_interval t, t_hit *h);

void			ft_free_objects(t_object *obj);
void			ft_free_lights(t_light *light);
t_light			*ft_copy_lights(t_light *old);
t_object		*ft_copy_objects(t_object *old);
t_scene			*ft_copy_scene(t_scene *old);

t_camera		ft_init_camera(t_vector lookfrom, t_vector lookat, double vfov);
t_scene			*ft_init_scene();
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

t_ray			ft_ray(t_vector a, t_vector b);
t_ray			ft_get_ray(t_camera *p, double u, double v);
t_vector		ft_ray_function(t_ray *r, double t);
double			ffmin(double a, double b);
double			ffmax(double a, double b);

t_vector		ft_rot_x(t_vector old, double theta);
t_vector		ft_rot_y(t_vector old, double theta);
t_vector		ft_rot_z(t_vector old, double theta);
t_vector		ft_rotcam_y(t_vector old, double theta);
t_vector		ft_rotcam_x(t_vector old, double theta);

int				ft_bg_col(int bg, int x, int y);
void			ft_object_selected(t_ptr *p);
void			ft_display_properties(t_ptr *p);
void			ft_display_moves(t_ptr *p);
void			ft_background(t_ptr *p);
char			*ft_ctoa(t_color c);
char			*ft_vtoa(t_vector v);
void			ft_menu_bar(t_ptr *p);

#endif
