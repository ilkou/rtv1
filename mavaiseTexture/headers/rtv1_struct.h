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
# include <float.h>
# include <pthread.h>
# include <stdio.h>

#define RAND48_SEED_0   (0x330e)
#define RAND48_SEED_1   (0xabcd)
#define RAND48_SEED_2   (0x1234)
#define RAND48_MULT_0   (0xe66d)
#define RAND48_MULT_1   (0xdeec)
#define RAND48_MULT_2   (0x0005)
#define RAND48_ADD      (0x000b)

# define WIN_WIDTH 800.0
# define WIN_HEIGHT (WIN_WIDTH / 2)
# define FRAME 7

# define C1(row) (row < FRAME || (row > WIN_HEIGHT - FRAME && row < WIN_HEIGHT))
# define C2(col) (col < FRAME || (col > WIN_WIDTH - FRAME && col < WIN_WIDTH))
# define CADRE(col, row) (C1(row) || C2(col))

# define NBTHREAD 4

# define DEFAULT_RI -2147483648.0

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
# define MLX_KEY_PAD_A 0
# define MLX_KEY_PAD_MINUS 78
# define MLX_KEY_PAD_PLUS 69
# define MLX_KEY_PAD_SPACE 49

# define THE_ABS(x) { x = x > 0 ? x : -x; }
# define RGB(x) (int)(255.99 * x)

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

typedef struct  s_texture
{
    int         nx;
    int         ny;
    int         *data;
}               t_texture;

typedef struct  s_hit
{
    double      t;
    double      u;
    double      v;
    t_vector    p;
    t_vector    normal;
    int			(*type)(t_vector albedo, t_ray *r_in, struct s_hit *rec, t_vector *att, t_ray *scattered);
    t_vector    material;
    int         nbr;
    t_texture   txtr;
}               t_hit;



typedef struct  s_sphere
{
    t_vector    center;
    double      ray;
    t_texture   t;
    t_vector    lamb;
    double      ref_idx;
	int			(*type)(t_vector albedo, t_ray *r_in, t_hit *rec, t_vector *att, t_ray *scattered);
}               t_sphere;

typedef struct  s_aabb
{
    t_vector    min;
    t_vector    max;
}               t_aabb;

typedef struct  s_o
{
    t_sphere    s;
    int			nbr_obj;
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
	t_vector	w;
	t_vector	u;
	t_vector	v;
	double      fov;
    double      half_h;
    double      half_w;
}				t_camera;

typedef struct	s_point
{
	int 		x;
	int			y;
}				t_point;

typedef struct	s_color
{
	int			a;
	int			b;
}				t_color;

typedef struct s_ptr1
{
    void		*img;
    int			*data;
    int			bpp;
    int			size;
    int			endian;
}               t_ptr1;

typedef struct	s_ptr
{
	void		*win;
	void		*mlx;
	void		*img;
	int			*data;
	int			*bpp;
	int			*size;
	int			*endian;
	double      antia;
	double      fuzz;
	double      cc;
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
	t_objects   *o;
}				t_thread;

#endif