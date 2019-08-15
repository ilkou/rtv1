/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 22:43:33 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 17:03:22 by oouklich         ###   ########.fr       */
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
	t_vector	trs;
	t_color		col;
	double		size;
	char		*name;
	int			(*hit)();
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
	double		pd;
	double		shininess;
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
