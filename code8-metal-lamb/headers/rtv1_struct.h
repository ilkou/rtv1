/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 22:43:33 by oouklich          #+#    #+#             */
/*   Updated: 2019/03/22 22:20:45 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
#include <float.h>
# include <pthread.h>

# define WIN_WIDTH 1300.0
# define WIN_HEIGHT (WIN_WIDTH / 2)

# define NBTHREAD 4

# define FRAME 7

# define MLX_KEY_PAD_LEFT 123
# define MLX_KEY_PAD_RIGHT 124
# define MLX_KEY_PAD_UP 126
# define MLX_KEY_PAD_DOWN 125
# define MLX_KEY_PAD_ESC 53
# define MLX_KEY_PAD_J 38
# define MLX_KEY_PAD_M 46
# define MLX_KEY_PAD_T 17
# define MLX_KEY_PAD_N 45
# define MLX_KEY_PAD_R 15
# define MLX_KEY_PAD_B 11
# define MLX_KEY_PAD_S 1
# define MLX_KEY_PAD_X 7
# define MLX_KEY_PAD_MINUS 78
# define MLX_KEY_PAD_PLUS 69
# define MLX_KEY_PAD_SPACE 49

# define THE_ABS(x) { x = x > 0 ? x : -x; }

typedef struct  s_vector
{
    double      v1;
    double      v2;
    double      v3;
}               t_vector;

typedef struct  s_ray
{
    t_vector    A;
    t_vector    B;
}               t_ray;

typedef struct  s_hit
{
    double      t;
    t_vector    p;
    t_vector    normal;
    t_vector    *material;
    int         nbr;
}               t_hit;

typedef struct  s_sphere
{
    t_vector    center;
    double      ray;
    t_vector    lamb;
}               t_sphere;

typedef struct  s_o
{
    t_sphere    *s;
    int         nbr_obj;
    struct s_o  *next;
}               t_objects;

typedef	struct	s_interval
{
	double		t_min;
	double		t_max;
}				t_interval;

typedef struct	s_camera
{
	t_vector	origin;
	t_vector	lower_left_corner;
	t_vector	horizontal;
	t_vector	vertical;
}				t_camera;

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_color
{
	int			a;
	int			b;
}				t_color;

typedef struct	s_ptr
{
	void		*win;
	void		*mlx;
	void		*img;
	int			*data;
	int			*bpp;
	int			*size;
	int			*endian;
	int			stop;
	int			color;
	t_point		seed;
	double		zoom;
	t_camera    cam;
	t_vector    center;
	double		(*object)(struct s_ptr *p, double col, double row);
}				t_ptr;

typedef struct	s_thread
{
	int			i;
	t_ptr		*e;
}				t_thread;

#endif