#include "rtv1.h"

void    ft_initial(t_ptr **p)
{
    (*p) = (struct s_ptr *)malloc(sizeof(struct s_ptr));
    (*p)->bpp = (int *)malloc(4);
    (*p)->size = (int *)malloc(4);
    (*p)->endian = (int *)malloc(4);
    (*p)->img = NULL;
    (*p)->mlx = NULL;
    (*p)->data = NULL;
    (*p)->win = NULL;

    (*p)->hud = 1;
	(*p)->spec = 0.0;
	(*p)->maxref = 0;
	(*p)->pref = 0;
	(*p)->selection = 0;
	(*p)->aa = 1;

    (*p)->obj = NULL;
	(*p)->light = NULL;

    ft_add_cam(*p);
    ft_add_light(*p);
    ft_add_sphere(*p);
}

void    ft_add_cam(t_ptr *p)
{
    p->cam_pos.x = 0;
	p->cam_pos.y = 0;
	p->cam_pos.z = -40;

    p->cam_dir.x = 0;
	p->cam_dir.y = 0.25;
	p->cam_dir.z = 1;
}


t_obj			*ft_add_light_link(t_ptr *p, t_obj *link)
{
	t_obj	*tete;

	tete = p->light;
	if (p->light == NULL)
		return (link);
	while (p->light->next != NULL)
		p->light = p->light->next;
	p->light->next = link;
	return (tete);
}

t_obj			*ft_add_object_link(t_ptr *p, t_obj *link)
{
	t_obj	*tete;

	tete = p->obj;
	if (p->obj == NULL)
		return (link);
	while (p->obj->next != NULL)
		p->obj = p->obj->next;
	p->obj->next = link;
	return (tete);
}

int			ft_add_light(t_ptr *p)
{
	t_obj	*link;

	if (!(link = (t_obj *)malloc(sizeof(t_obj))))
		return (-1);

	link->col.red = 250;
	link->col.green = 250;
	link->col.blue = 250;

	link->pos.x = 20;
	link->pos.y = 10;
	link->pos.z = 20;

	link->next = NULL;
	p->light = ft_add_light_link(p, link);

	return (0);
}


int			ft_add_sphere(t_ptr *p)
{
	t_obj	*link;
	t_obj	*link2;

	if (!(link = (t_obj *)malloc(sizeof(t_obj))))
		return (-1);
	if (!(link2 = (t_obj *)malloc(sizeof(t_obj))))
		return (-1);
	link->type = 4;

	link->col.red = 255;
	link->col.green = 0;
	link->col.blue = 0;

    link->pos.x = 0;
	link->pos.y = 0;
	link->pos.z = 0;

	link->size = 10;

	link->next = link2;
	link2->type = 4;

	link2->col.red = 0;
	link2->col.green = 255;
	link2->col.blue = 0;

    link2->pos.x = 0;
	link2->pos.y = -1000;
	link2->pos.z = 0;

	link2->size = 990;

	link2->next = NULL;

	p->obj = ft_add_object_link(p, link);
	return (0);
}

int main()
{
    t_ptr   *p;
    
   /* if(argc != 2)
    {
        ft_putstr("usage: ./rtv1  [scene]\n");
        return(0);
    }
    */
    ft_initial(&p);
    ft_creat_window(p);
    ft_creat_image(p);
    ft_draw(p);
    mlx_hook(p->win, 2, 0, ft_deal_key, p);
    mlx_hook(p->win, 4, 0, ft_mouse_press, p);
    mlx_loop(p->mlx);
}
