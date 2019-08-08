/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 22:43:33 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/08 21:15:57 by oouklich         ###   ########.fr       */
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

# define PS p->scene
# define MSP mlx_string_put

# define FRAME 10
# define MENU_BAR 150
# define IMG_WIDTH 1000.0
# define IMG_HEIGHT (IMG_WIDTH / 2)
# define WIN_WIDTH (IMG_WIDTH + (2 * FRAME))
# define WIN_HEIGHT (IMG_HEIGHT + FRAME + MENU_BAR)

# define COND_SLCT1(x) (x > FRAME && x < IMG_WIDTH + FRAME)
# define COND_SLCT2(y) (y > MENU_BAR && y < IMG_HEIGHT + MENU_BAR)
# define COND_SELECT(x, y) (COND_SLCT1(x) && COND_SLCT2(y))

# define BG_COL_1 0xAAAAAA
# define BG_COL_2 0xB8B8B8
# define BG_COL_3 0x3E3E3d
# define BG_COL_4 0x797978

# define COL1 0x333333
# define COL2 0x000000

# define COND_BG1(row) (row > FRAME && row < MENU_BAR - FRAME)
# define COND_BG2(col) (col > FRAME && col < WIN_WIDTH - FRAME)
# define BG_COND(row, col) (COND_BG1(row) && COND_BG2(col))
# define RWH(row) (row < WIN_HEIGHT - FRAME)
# define CWW(col) (col < WIN_WIDTH - FRAME)
# define BG_COND1(row, col) (col == FRAME && row > MENU_BAR && RWH(row))
# define BG_COND2(row, col) (row == MENU_BAR && col > FRAME && CWW(col))

# define NBTHREAD 4

# define DEFAULT -2147483648.0

# define MLX_KEY_LEFT 123
# define MLX_KEY_RIGHT 124
# define MLX_KEY_UP 126
# define MLX_KEY_DOWN 125
# define MLX_KEY_ESC 53
# define MLX_KEY_ENTER 36
# define MLX_KEY_J 38
# define MLX_KEY_M 46
# define MLX_KEY_T 17
# define MLX_KEY_N 45
# define MLX_KEY_R 15
# define MLX_KEY_B 11
# define MLX_KEY_S 1
# define MLX_KEY_X 7
# define MLX_KEY_Y 16
# define MLX_KEY_Z 6
# define MLX_KEY_A 0
# define MLX_KEY_O 31
# define MLX_KEY_C 8
# define MLX_KEY_L 37
# define MLX_KEY_MINUS 78
# define MLX_KEY_PLUS 69
# define MLX_KEY_SPACE 49

# define THE_ABS(x) { x = x > 0 ? x : -x; }
# define RGB(x) (int)(255.99 * x)
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))

# define SPHERE 1
# define CYLINDER 2
# define CONE 3
# define PLANE 4

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_vector
{
	double		v1;
	double		v2;
	double		v3;
}				t_vector;

# define VEC(a, b, c) (t_vector){a, b, c}

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

# define COL(a, b, c) (t_color){a, b, c}

typedef struct	s_ray
{
	t_vector	origin;
	t_vector	dir;
}				t_ray;

typedef struct	s_o
{
	t_vector	pos;
	t_vector	rot;
	t_color		col;
	double		size;
	char		*name;
	int			(*hit)();
	int			type;
	struct s_o	*next;
}				t_object;

typedef	struct	s_interval
{
	double		t_min;
	double		t_max;
}				t_interval;

# define I(a, b) (t_interval){a, b}

typedef	struct	s_l
{
	t_vector	pos;
	t_vector	dir;
	t_color		col;
	double		intensity;
	struct s_l	*next;
}				t_light;

typedef struct	s_hit
{
	t_object	*curr_obj;
	t_vector	p;
	t_vector	n;
	t_vector	oc;
	t_vector	temp;
	t_color		col;
	t_ray		ray;
	double		t;
	double		coef[3];
	double		r[2];
	double		delta;
	int			(*hit)();
}				t_hit;

typedef struct	s_camera
{
	t_vector	origin;
	t_vector	lower_left_corner;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	lookat;
	t_vector	w;
	t_vector	u;
	t_vector	v;
	double		fov;
	double		half_h;
	double		half_w;
}				t_camera;

typedef struct	s_scene
{
	t_camera	cam;
	t_light		*light;
	t_object	*object;
	t_object	*curr_object;
	t_hit		record;
	double		theta;
	double		anti_a;
	double		coef_spec;
	double		brillance;
	int			spec;
}				t_scene;

typedef struct	s_ptr1
{
	void		*img;
	int			*data;
	int			bpp;
	int			size;
	int			endian;
}				t_ptr1;

typedef struct	s_ptr
{
	void		*win;
	void		*mlx;
	void		*img;
	int			*data;
	int			*bpp;
	int			*size;
	int			*endian;
	int			cam_slct;
	int			light_slct;
	int			inc_dec;
	t_light		*curr_light;
	t_scene		*scene;
}				t_ptr;

typedef struct	s_thread
{
	int			i;
	t_ptr		*e;
	t_scene		*scene;
}				t_thread;

#endif
