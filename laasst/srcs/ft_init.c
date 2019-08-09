/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:02:31 by oouklich          #+#    #+#             */
/*   Updated: 2019/04/17 19:17:28 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

void	ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
	if (x >= 0 && x < IMG_WIDTH
			&& y >= 0 && y < IMG_HEIGHT)
	{
		p->data[y * (int)IMG_WIDTH + x] = color;
	}
}

void	ft_create_window(t_ptr *p)
{
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HEIGHT, "rtv1");
}

void	ft_create_image(t_ptr *p)
{
	p->img = mlx_new_image(p->mlx, IMG_WIDTH, IMG_HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, p->bpp, p->size, p->endian);
}

t_camera    ft_init_camera(t_vector lookfrom, t_vector lookat, double vfov)
{
    t_camera    c;
    t_vector    vup;

    vup = VEC(0, 1, 0);
    c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
    c.half_w = (IMG_WIDTH / IMG_HEIGHT) * c.half_h;
    c.origin = lookfrom;
    c.w = ft_normalize(ft_sub(lookat, lookfrom));
    c.u = ft_normalize(ft_cross(c.w, vup));
    c.v = ft_cross(c.u, c.w);
    c.lower_left_corner = ft_sub(c.origin, ft_add(ft_pro_k(c.v, c.half_h), ft_pro_k(c.u, c.half_w)));
    c.lower_left_corner = ft_add(c.lower_left_corner, c.w);
    c.horizontal = ft_pro_k(c.u, 2.0 * c.half_w);
    c.vertical =  ft_pro_k(c.v, 2.0 * c.half_h);
    c.fov = vfov;
    return (c);
}

t_object   *ft_get_objects()
{
    t_object   *obj0, *obj, *obj2, *obj3;

    if (!(obj0 = (struct s_o*)malloc(sizeof(struct s_o))))
        return (NULL);
    if (!(obj = (struct s_o*)malloc(sizeof(struct s_o))))
        return (NULL);
    if (!(obj2 = (struct s_o*)malloc(sizeof(struct s_o))))
        return (NULL);
    if (!(obj3 = (struct s_o*)malloc(sizeof(struct s_o))))
        return (NULL);
    obj0->col = COL(1, 1, 0.3);
    obj0->pos = VEC(3.1, 0.55, -1.9);
    obj0->rot = ft_normalize(VEC(0, 1, 0));
    obj0->size = 1;
    obj0->hit = ft_hit_cylinder;
    obj0->name = ft_strdup("CYLINDER");
    obj0->type = CYLINDER;
    obj0->next = obj;

    obj->col = COL(1.0, 0, 0);
    obj->pos = VEC(0, 0, 0);
    obj->rot = VEC(0.0, 0.0, 0.0);
    obj->size = 1.0;
    obj->hit = ft_hit_sphere;
    obj->name = ft_strdup("SPHERE");
    obj->type = SPHERE;
    obj->next = obj2;

    obj2->col = COL(0.1, 0.9, 0.8);
    obj2->pos = VEC(0, -1, -100);
    obj2->rot = ft_normalize(VEC(0, 1, 0));
    obj2->size = 0.0;
    obj2->hit = ft_hit_plane;
    obj2->name = ft_strdup("PLANE");
    obj2->type = PLANE;
    obj2->next = obj3;

    obj3->col = COL(1, 0, 0.4);
    obj3->pos = VEC(-1, 1.0, 1);
    obj3->rot = ft_normalize(VEC(0, 1, 0));
    obj3->size = 60;
    obj3->hit = ft_hit_cone;
    obj3->name = ft_strdup("CONE");
    obj3->type = CONE;
    obj3->next = NULL;
    return (obj0);
}

t_light     *ft_get_lights()
{
    t_light     *light, *light2;

    if (!(light = (struct s_l*)malloc(sizeof(struct s_l))))
        return (NULL);
    if (!(light2 = (struct s_l*)malloc(sizeof(struct s_l))))
        return (NULL);
    light->col = COL(1.0, 1.0, 1.0);
    light->pos = VEC(100, 50, 0);
    light->intensity = 0.18;
    light->next = light2;
    light2->col = COL(1.0, 1.0, 1.0);
    light2->pos = VEC(-20, -50, 70);
    light->intensity = 0.18;
    light2->next = NULL;
    return (light);
}

t_scene     *ft_init_scene()
{
    t_scene     *scene;

    if (!(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
        return (NULL);
    scene->anti_a = 3.0;
    scene->cam = ft_init_camera(VEC(0, 0, 5), VEC(0, 0, 0), 60.0);
    scene->object = ft_get_objects();
    scene->light = ft_get_lights();
    scene->coef_spec = 4.0;
    scene->brillance = 30.0;
    scene->spec = 1;
    scene->theta = 45.0 / 2.0;
    scene->curr_object = NULL;
    return (scene);
}

void	ft_init(t_ptr *p, char **argv)
{
	p->img = NULL;
	p->mlx = NULL;
	p->data = NULL;
	p->win = NULL;
	p->bpp = malloc(4);
	p->size = malloc(4);
	p->endian = malloc(4);
	p->inc_dec = 1;
    p->cam_slct = 0;
    p->light_slct = 0;
    p->curr_light = NULL;
	p->scene = ft_init_scene();
}
