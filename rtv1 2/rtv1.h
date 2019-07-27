/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:55:59 by mel-jadi          #+#    #+#             */
/*   Updated: 2019/07/07 20:32:25 by mel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "./libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <math.h>

# define MLX_KEY_PAD_MINUS 78
# define MLX_KEY_PAD_PLUS 69
# define MLX_KEY_PAD_LEFT 123
# define MLX_KEY_PAD_RIGHT 124
# define MLX_KEY_PAD_UP 126
# define MLX_KEY_PAD_DOWN 125
# define MLX_KEY_PAD_P 35
# define MLX_KEY_PAD_I 34
# define MLX_KEY_PAD_T 17
# define MLX_KEY_PAD_W 13
# define MLX_KEY_PAD_Z 6
# define MLX_KEY_PAD_C 8
# define MLX_KEY_PAD_R 15
# define MLX_KEY_PAD_W 13
# define MLX_KEY_PAD_S 1
# define MLX_KEY_PAD_ESC 53

# define IMG_WIDTH  800
# define IMG_HEIGHT 800

# define FOV 2.0

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct        s_color
{
    float            red;
    float            green;
    float            blue;
}                    t_color;

typedef struct        s_obj
{
    int                type;
    float              size;
    t_vec              rot;
    t_vec              pos;
    t_color            col;
    struct s_obj      *next;
}                     t_obj;

typedef struct		s_ptr
{
	void			*win;
	void			*mlx;
	void			*img;
	int				*data;
	int				*bpp;
	int				*size;
	int				*endian;

    t_vec			cam_pos;
	t_vec			cam_dir;

    t_vec			ray_dir;

    t_obj			*light;
    t_obj			*obj;

    int				hud;
	int				selection;
	int				maxref;
	int				pref;
	int				aa;
    float			spec;

}					t_ptr;

typedef struct		s_th
{
	int				maxref;
	int				pref;
	int				cpt;
	int				ty;
	int				tx;
	int				aa;
	int			*data;
	t_vec			i;
	t_vec			j;
	t_vec			k;
	t_vec			cam_pos;
	t_vec			cam_dir;
	t_vec			ray_dir;
	t_vec			norm;
	t_vec			ref;
	t_vec			dist;
	t_vec			refpos;
	t_obj			*obj;
	t_obj			*light;
	float			spec;
	float			t0;
	float			t1;
	float			t;
	float			a;
	float			b;
	float			c;
}					t_th;


void    ft_mlx_putpixel(t_th *p, int x, int y, int color);
void    ft_creat_window(t_ptr *p);
void    ft_creat_image(t_ptr *p);
void    ft_write_img(t_ptr *p);
void    ft_draw(t_ptr *p);
int     ft_deal_key(int key, t_ptr *p);
int     ft_mouse_press(int button, int x, int y, t_ptr *p);
void    ft_initial(t_ptr **p);
void	ft_copy(t_ptr *p, t_th *th);
t_obj    *copy_obj(t_obj *obj);


void    ft_add_cam(t_ptr *p);
int		ft_add_light(t_ptr *p);
t_obj	*ft_add_light_link(t_ptr *p, t_obj *link);
int		ft_add_sphere(t_ptr *p);
t_obj	*ft_add_object_link(t_ptr *p, t_obj *link);


int		ft_raytrace(t_th *p, t_obj *node, double x, double y);
float	*ft_lambert(t_th *p, t_obj *tmp, t_obj *light, float *tab);
float	*ft_endlight(t_obj *tmp, t_obj *light, float *tab, float d);
int		ft_shadow(t_th *p, t_obj *tmp, t_obj *light, t_vec pos);
t_vec	ft_norm(t_th *p, t_obj *tmp, t_vec pos);
float	ft_spec(t_th *p, t_vec dist, float d, float lambert);
float	*ft_set_ray(t_th *p, float *tab, double x, double y);
t_obj	*ft_intersection(t_th *p, t_obj *node, t_vec ray, t_vec pos);
double	ft_inter_sphere(t_th *p, t_obj *tmp, t_vec ray, t_vec pos);
t_obj	*ft_ref_init(t_th *p, t_obj *tmp, t_vec *pos);
t_obj	*ft_ref_inter(t_th *p, t_obj *node, t_obj *tmp, t_vec pos);
float   *ft_reflect(t_th *p, t_obj *tmp, t_vec *pos, float *tab);
float	ft_clamp(float value, float min, float max);
float	*ft_average(float *r, float *tab);
void	ft_fzero(float *s, int n);



t_vec	ft_vectorscale(t_vec *v, float n);
t_vec	ft_vectorsub(t_vec *v1, t_vec *v2);
t_vec	ft_vectorcross(t_vec *v1, t_vec *v2);
void	ft_vectornorm(t_vec *v);
float	ft_vectordot(t_vec *v1, t_vec *v2);


#endif
