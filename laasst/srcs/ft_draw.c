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

t_vector    ft_reflect(t_vector v, t_vector n)
{
    return (ft_sub(v, ft_pro_k(ft_pro_k(n, 2), ft_dot(v, n))));
}

double	ft_clamping(double value)
{
    if (value < 0.0)
        value = 0.0;
    if (value > 1.0)
        value = 1.0;
    return (value);
}
void    ft_adjustment(t_color *c)
{
    c->r = ft_clamping(c->r);
    c->g = ft_clamping(c->g);
    c->b = ft_clamping(c->b);
}

int		ft_shading(t_scene *scene, t_light *light)
{
    t_ray       r;
    t_hit       rec;
    t_object	*obj;
    double      closest_so_far;

    obj = scene->object;
    r.dir = ft_sub(light->pos, scene->record.p);
    closest_so_far = sqrtf(ft_dot(r.dir, r.dir));
    r.origin = scene->record.p;
    r.dir = ft_normalize(r.dir);
    while (obj != NULL)
    {
        if (obj != scene->record.curr_obj)
            if (ft_hit(obj, r, I(0.0001, closest_so_far), &rec))
                return (1);
        obj = obj->next;
    }
    return (0);
}

double	ft_speculaire(t_scene *s, t_vector light_vec, double d)
{
    t_vector	reflected;
    double	spec;
    double	n_dot_l;

    spec = 0.0;
    light_vec = ft_normalize(light_vec);
    reflected = ft_reflect(light_vec, s->record.n);
    n_dot_l = ft_dot(reflected, s->record.ray.dir);
    if (n_dot_l > 0.0)
        spec = pow(n_dot_l, s->brillance) * s->coef_spec * d;
    return (ft_clamping(spec));
}

void		ft_illumination(t_scene *s, t_light *l, t_color *col) //modele de phong
{
    t_vector	light_vec;
    t_object    obj;
    double      coef;
    double      d;

    obj = *s->record.curr_obj;
    if (!l)
        *col = ft_pro_kc(ft_pro_c(obj.col, COL(1.0, 1.0, 1.0)), 0.15); //lumiere ambiante
    while (l != NULL)
    {
        coef = l->intensity;
        light_vec = ft_sub(l->pos, s->record.p);
        if (!ft_shading(s, l))
            coef += ft_clamping(ft_dot(ft_normalize(light_vec), s->record.n)); //lumiere diffuse
        d = ft_clamping((1.0 / sqrtf(sqrtf(ft_dot(light_vec, light_vec)))));
        coef = ft_clamping(coef * s->coef_spec * d);
        *col = ft_add_c(*col, ft_pro_kc(ft_pro_c(obj.col, l->col), coef));
        if (!ft_shading(s, l) && s->spec) //we have to verify if we had to check the shading or not
            *col = ft_add_kc(*col, ft_speculaire(s, light_vec, d));
        l = l->next;
    }
}

t_color    ft_raytrace_color(t_scene *s, t_ray *r, t_object *o, int depth)
{
    t_color color;

    color = COL(0.0, 0.0, 0.0);
    if (ft_hit(o, *r, I(0.0001, DBL_MAX), &s->record))
        ft_illumination(s, s->light, &color);
    ft_adjustment(&color);
    return (color);

}

t_color        ray_tracing(t_scene *scene, int col, int row)
{
    t_color    c;
    t_ray       r;
    int         ss;

    c = COL(0, 0, 0);
    ss = -1;
    while (++ss < (int)scene->anti_a)
    {
        r = ft_get_ray(&scene->cam, col, row);
        c = ft_add_c(c, ft_raytrace_color(scene, &r, scene->object, 0));

    }
    c = ft_div_kc(c, scene->anti_a);
    return (c);
}

void            *ft_calcul(t_thread *p)
{
    t_color     c;
    int         color;
    int		    col;
    int		    row;

    row = IMG_HEIGHT + 1;
    while (--row >= 0)
    {
        col = (int)(p->i * IMG_WIDTH / NBTHREAD) - 1;
        while (++col < (int)((p->i + 1) * IMG_WIDTH / NBTHREAD))
        {
            c = ray_tracing(p->scene, col, row);
            color = ft_from_rgb(RGB(c.r), RGB(c.g), RGB(c.b));
            ft_mlx_putpixel(p->e, col, IMG_HEIGHT - row, color);
        }
    }
    ft_free_objects(p->scene->object);
    ft_free_lights(p->scene->light);
    if (p->scene->curr_object)
        ft_free_objects(p->scene->curr_object);
    free(p->scene);
    pthread_exit(NULL);
}

void			ft_begin(t_ptr *p)
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].e = p;
		div[i].i = i;
		div[i].scene = ft_copy_scene(p->scene);
		pthread_create(&thread[i], NULL, (void*)ft_calcul, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
}

int			ft_draw(t_ptr *p)
{
    ft_bzero(p->data, IMG_WIDTH * IMG_HEIGHT * 4);
    ft_background(p);
	ft_begin(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, FRAME, MENU_BAR);
    return (1);

}
