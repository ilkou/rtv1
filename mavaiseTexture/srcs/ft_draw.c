/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:04:46 by oouklich          #+#    #+#             */
/*   Updated: 2019/03/22 22:22:08 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

/*t_point rgb_to_hex(int rgb)
{
	t_point p;

	p.y = rgb % 16;
	p.x = (rgb / 16) % 16;
	return (p);
}

int hex_to_int(t_point r, t_point g, t_point b)
{
	return ((int)r.x * 16 * 16 * 16 * 16 * 16 + (int)r.y * 16 * 16 * 16 * 16 +
	(int)g.x * 16 * 16 * 16 + (int)g.y * 16 * 16 + (int)b.x * 16 + (int)b.y);
}*/

t_ptr1            ft_mlx_load_image(void *mlx_ptr, char *filename, t_point size)
{
    t_ptr1        p;

    p.img = mlx_xpm_file_to_image(mlx_ptr, filename, &size.x, &size.y);
    if (!p.img)
    {
        ft_putendl("File !!");
        ft_putendl(filename);
        exit(0);
    }
    p.data = (int *)mlx_get_data_addr(p.img, &p.bpp, &p.size,
                                      &p.endian);
    return (p);
    //t_ptr1 m = ft_mlx_load_image(p->mlx, "loading.xpm", ft_point(284, 160));
    //    mlx_put_image_to_window(p->mlx, p->win, m.img, (WIN_WIDTH / 2) - 142, (WIN_HEIGHT / 2) - 80);
}

int ft_from_rgb(int x, int y, int z)
{
    t_point r;
    t_point g;
    t_point b;

    r.y = x % 16;
    r.x = (x / 16) % 16;
    g.y = y % 16;
    g.x = (y / 16) % 16;
    b.y = z % 16;
    b.x = (z / 16) % 16;
    return ((int)r.x * 16 * 16 * 16 * 16 * 16 + (int)r.y * 16 * 16 * 16 * 16 +
    (int)g.x * 16 * 16 * 16 + (int)g.y * 16 * 16 + (int)b.x * 16 + (int)b.y);
}

/*double  hit_sphere(t_vector a, double ray, t_ray r)
{
    t_vector    oc;
    double      delta[4];

    oc = ft_diff(r.A, a);
    delta[0] = ft_dot(r.B, r.B);
    delta[1] = 2.0 * ft_dot(oc, r.B);
    delta[2] = ft_dot(oc ,oc) - (ray * ray);
    delta[3] = delta[1] * delta[1] - 4 * delta[0] * delta[2];
    if (delta[3] < 0)
        return (-1.0);
    else
        return (-delta[1] - sqrt(delta[3]) / (2.0 * delta[0]));
}*/
/*double      t;

    t = hit_sphere(p->center, 0.5, r);
    if (t > 0.0)
    {
        t_vector N = ft_to_unit_vector(ft_diff(ft_ray_function(r, t), ft_vector(0,0,-1)));
        return (ft_pro_d(ft_vector(N.v1+1, N.v2+1, N.v3+1), 0.5));
    }*/

t_vector    ft_rand_in_unit_disk()
{
    t_vector    p;

    p = ft_vector(1,1,0);
    while (ft_dot(p,p) >= 1.0)
        p = ft_diff(ft_pro_d(ft_vector(myrand48(), myrand48(), 0), 2.0), ft_vector(1,1,0));
    return (p);
}

t_vector    ft_rand_in_unit_sphere()
{
    t_vector    p;

    p = ft_vector(1,1,0);
    while (ft_lengthsquared(p) >= 1.0)
        p = ft_diff(ft_pro_d(ft_vector(myrand48(), myrand48(), myrand48()), 2.0), ft_vector(1,1,1));
    return (p);
}

int         ft_schlick(double cos, double ref_idx)
{
    double  r0;

    r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return (r0 + (1 - r0) * pow(1 - cos, 5));
}

t_vector    ft_reflect(t_vector v, t_vector n)
{
    return (ft_diff(v, ft_pro_d(ft_pro_d(n, 2), ft_dot(v, n)))); //v - 2*dot(v,n)*n reflection
}
int         ft_refract(t_vector *v, t_vector *n, double ni_over_nt, t_vector *refracted)
{
    t_vector    uv;
    double      dt;
    double      delta;

    uv = ft_to_uv(*v);
    dt = ft_dot(uv, *n);
    delta = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (delta > 0)
        *refracted = ft_diff(ft_pro_d(ft_diff(uv, ft_pro_d(*n, dt)), ni_over_nt), ft_pro_d(*n, sqrt(delta)));
    return (delta > 0);
}

int     ft_scatter_dielectric(t_vector ref_idx, t_ray *r, t_hit *rec, t_vector *att, t_ray *scattered)
{
    t_vector    outward_normal;
    t_vector    reflected;
    t_vector    refracted;
    double      ni_over_nt;
    double      reflect_prob;
    double      cos;

    reflected = ft_reflect(r->B, rec->normal);
    *att = ft_vector(1.0, 1.0, 1.0);
    outward_normal = (ft_dot(r->B, rec->normal) > 0) ? ft_diff(ft_vector(0,0,0),
            rec->normal) : rec->normal;
    ni_over_nt = (ft_dot(r->B, rec->normal) > 0) ? ref_idx.v1 : 1.0 / ref_idx.v1;
    cos = (ft_dot(r->B, rec->normal) > 0) ? ref_idx.v1 * ft_dot(r->B, rec->normal)
            / ft_length(r->B) : - ft_dot(r->B, rec->normal) / ft_length(r->B);
    reflect_prob = (ft_refract(&r->B, &outward_normal, ni_over_nt, &refracted))
            ? ft_schlick(cos, ref_idx.v1) : 1.0;
    *scattered = (ft_refract(&r->B, &outward_normal, ni_over_nt, &refracted)) ?
            *scattered : ft_ray(rec->p, reflected);
    *scattered = (myrand48() < reflect_prob) ? ft_ray(rec->p, reflected) :
            ft_ray(rec->p, refracted);
    return (1);
}

int     ft_scatter_lambertian1(t_vector albedo, t_ray *r_in, t_hit *rec, t_vector *att, t_ray *scattered)
{
    t_vector    target;
    double      sines;

    sines = tan(10 * rec->p.v1) * tan(10 * rec->p.v2) * tan(10 * rec->p.v3);
    target = ft_add(ft_add(rec->p, rec->normal), ft_pro_d(ft_rand_in_unit_sphere(), 0.8));
    *scattered = ft_ray(rec->p, ft_diff(target, rec->p));
    if (albedo.v1 == -500)
        *att = sines < 0 ? (t_vector){0.2,0.3,0.1} : (t_vector){0.9, 0.9, 0.9};
    else
        *att = albedo;
    return (1);
}

void        get_sphere_uv(t_vector p, double *u, double *v)
{
    double  phi;
    double  theta;

    phi = atan2(p.v3, p.v1);
    theta = asin(p.v2);
    *u = 1.0 - (phi + M_PI) / (2.0 * M_PI);
    *v = (theta + M_PI / 2.0) / M_PI;
}

t_vector    image_texture(t_texture p, double u, double v)
{
    int     i;
    int     j;

    i = u * p.nx;
    j = (1 - v) * p.ny - 0.001;
    (i < 0) ? i = 0 : i;
    (j < 0) ? j = 0 : j;
    (i > p.nx - 1) ? i = p.nx - 1 : i;
    (j > p.ny - 1) ? j = p.ny - 1 : j;
    return (ft_vector((int)p.data[3 * i + 3 * p.nx * j] / 255.0,
                      (int)p.data[3 * i + 3 * p.nx * j + 1] / 255.0,
                      (int)p.data[3 * i + 3 * p.nx * j + 2] / 255.0));
}

int     ft_scatter_lambertian2(t_vector albedo, t_ray *r_in, t_hit *rec, t_vector *att, t_ray *scattered)
{
    t_vector    target;

    target = ft_add(ft_add(rec->p, rec->normal), ft_pro_d(ft_rand_in_unit_sphere(), 0.8));
    *scattered = ft_ray(rec->p, ft_diff(target, rec->p));
    if (albedo.v1 != -500)
        *att = image_texture(rec->txtr, rec->u, rec->v);
    else
        *att = albedo;
    return (1);
}

int     ft_scatter_metal(t_vector albedo, t_ray *r_in, t_hit *rec, t_vector *att, t_ray *scattered)
{
    t_vector    reflected;

    reflected = ft_reflect(ft_to_uv(r_in->B), rec->normal);
    *scattered = ft_ray(rec->p, reflected);
    *att = albedo;
    return (ft_dot(scattered->B, rec->normal) > 0);
}

t_ptr1  ft_load_texture(void *mlx_ptr, char *filename, t_point size)
{
    t_ptr1      p;

    p.img = mlx_xpm_file_to_image(mlx_ptr, filename, &size.x, &size.y);
    if (!p.img)
    {
        ft_putendl("File !!");
        ft_putendl(filename);
        exit(0);
    }
    p.data = (int *)mlx_get_data_addr(p.img, &p.bpp, &p.size,
                                      &p.endian);
    return (p);
}
/*void	ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
    if (x >= 0 && x < WIN_WIDTH
        && y >= 0 && y < WIN_HEIGHT)
    {
        p->data[y * (int)WIN_WIDTH + x] = color;
    }
}*/
int     *get_data(t_ptr1 *p, int x, int y)
{
    int *ret = (int *)malloc(sizeof(int) * x * y);
    int i, j;
    i = 0;
    j = 0;
    while (i < x)
    {
        j = 0;
        while (j < y)
        {
            ret[i * y + j] = p->data[i * y + j];
            j++;
        }
        i++;
    }
    return (ret);
}

t_objects *random_scene(t_ptr *p) {
    int n = 500;
    int i = 1;
    float choose_mat;
    t_vector center;
    t_objects *list;
    t_texture t;
    t_ptr1 p1 = ft_load_texture(p->mlx, "earthmap.xpm", ft_point(318, 159));
    t.data = get_data(&p1, 318, 159);
    t.nx = 318;
    t.ny = 159;
    if (!(list = (struct s_o*)malloc(sizeof(struct s_o) * (n + 1))))
        return (NULL);
    list[0].s = ft_sphere(ft_vector(0,-1000,0), 1000, ft_vector(0.5, 0.5, 0.5));
    list[0].s.type = ft_scatter_lambertian1;
    //list[i++].s = ft_sphere_dielec(ft_vector(0, 1, 0), 1.0, 1.5);
    //list[i - 1].s.type = ft_scatter_dielectric;
    list[i++].s = ft_sphere_texture(ft_vector(-4, 1, 0), 1.0, t);
    list[i - 1].s.type = ft_scatter_lambertian2;
    //list[i++].s = ft_sphere(ft_vector(4, 1, 0), 1.0, ft_vector(0.7, 0.6, 0.5));
    //list[i - 1].s.type = ft_scatter_metal;
    list[0].nbr_obj = i;
    return (list);
}

t_vector    ft_color(t_ray *r, t_ptr *p, t_objects *o, int depth)
{
    t_vector    unit;
    double      k;
    t_hit       rec;

    if (depth < 50 && ft_hit(o, r, ft_interval(0.001, DBL_MAX), &rec))
    {
        t_ray       scattered;
        t_vector    att;
        if (rec.type(rec.material, r, &rec, &att, &scattered))
            return (ft_pro(att, ft_color(&scattered, p, o, depth+1)));
        else
            return (ft_vector(0,0,0));
    }
    unit = ft_to_uv(r->B);
    k = 0.5 * (unit.v2 + 1.0);
    return (ft_add(ft_pro_d(ft_vector(1, 1, 1), (1.0 - k)),
                   ft_pro_d(ft_vector(0.5, 0.7, 1), k)));
}

void            *ft_calcul(t_thread *p)
{
    double	iteration;
    int		col;
    int		row;
    int     ss;

    row = WIN_HEIGHT + 1;
    while (--row >= 0)
    {
        col = (int)(p->i * WIN_WIDTH / NBTHREAD) - 1;
        while (++col < (int)((p->i + 1) * WIN_WIDTH / NBTHREAD))
        {
            t_vector c = ft_vector(0,0,0);
            ss = -1;
            while (++ss < (int)p->e->antia)
            {
                t_ray r = ft_get_ray(&p->e->cam, col, row);
                c = ft_add(c, ft_color(&r, p->e, p->o, 0));

            }
            c = ft_div_d(c, p->e->antia);
            c = ft_vector(sqrt(c.v1), sqrt(c.v1), sqrt(c.v3));
            t_vector w = ft_vector((double)col / WIN_WIDTH, (double)row / WIN_HEIGHT, 0.2);
            if (CADRE(col,row))
                ft_mlx_putpixel(p->e, col, row, ft_from_rgb(RGB(w.v1),
                        RGB(w.v2), RGB(w.v3)));
            else
                ft_mlx_putpixel(p->e, col, WIN_HEIGHT - row,
                        ft_from_rgb(RGB(c.v1), RGB(c.v2), RGB(c.v3)));
        }
    }
    pthread_exit(NULL);
}

void            ft_background(t_ptr *p)
{
    int		    col;
    int         row;

    row = WIN_HEIGHT + 1;
    while (--row >= 0)
    {
        col = -1;
        while (++col < WIN_WIDTH)
            mlx_pixel_put(p->mlx, p->win, col, row, 0x20);
    }
    mlx_string_put(p->mlx, p->win, WIN_WIDTH / 2 - 50, WIN_HEIGHT / 2, 0xFFFFFF, "LOADING...");
}

void			ft_cadre(t_ptr *p)
{
    int		    col;
    int         row;
    t_vector    w;

    row = WIN_HEIGHT + 1;
    while (--row >= 0)
    {
        col = -1;
        while (++col < WIN_WIDTH)
        {
            w = ft_vector((double)col / WIN_WIDTH, (double)row / WIN_HEIGHT, 0.2);
            if (CADRE(col, row))
                mlx_pixel_put(p->mlx, p->win, col, row, ft_from_rgb(RGB(w.v1), RGB(w.v2), RGB(w.v3)));
        }
    }
    mlx_string_put(p->mlx, p->win, WIN_WIDTH / 2 - 50, WIN_HEIGHT / 2, 0xFFFFFF, "DEBUGGING");
}

void			ft_begin(t_ptr *p)
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	t_objects   *obj = random_scene(p);
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].e = p;
		div[i].i = i;
		div[i].o = obj;
		pthread_create(&thread[i], NULL, (void*)ft_calcul, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
}

int			ft_draw(t_ptr *p)
{
    ft_bzero(p->data, WIN_WIDTH * WIN_HEIGHT * 4);
	ft_begin(p);
	/*ft_putnbr((int)p->antia);
	ft_putendl("");*/
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
    return (1);

}
