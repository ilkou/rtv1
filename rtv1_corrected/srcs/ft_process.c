/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:54:03 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/16 17:00:27 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

void		ft_free_objects(t_object *object)
{
	t_object	*obj;
	t_object	*tmp;

	obj = object;
	while (obj != NULL)
	{
		tmp = obj->next;
		free(obj->name);
		free(obj);
		obj = tmp;
	}
}

void		ft_free_lights(t_light *light)
{
	t_light		*l;
	t_light		*tmp;

	l = light;
	while (l != NULL)
	{
		tmp = l->next;
		free(l);
		l = tmp;
	}
}

t_light		*ft_copy_lights(t_light *old)
{
	t_light		*new;

	if (!old || !(new = (struct s_l*)malloc(sizeof(struct s_l))))
		return (NULL);
	new->pos = old->pos;
	new->col = old->col;
	new->intensity = old->intensity;
	new->next = NULL;
	if (old->next)
		new->next = ft_copy_lights(old->next);
	return (new);
}

t_object	*ft_copy_objects(t_object *old)
{
	t_object	*new;

	if (!old || !(new = (struct s_o*)malloc(sizeof(struct s_o))))
		return (NULL);
	new->pos = old->pos;
	new->col = old->col;
	new->hit = old->hit;
	new->size = old->size;
	new->rot = old->rot;
	new->name = ft_strdup(old->name);
	new->next = NULL;
	if (old->next)
		new->next = ft_copy_objects(old->next);
	return (new);
}

t_scene		*ft_copy_scene(t_scene *old)
{
	t_scene		*scene;

	if (!old || !(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		return (NULL);
	scene->light = ft_copy_lights(old->light);
	scene->object = ft_copy_objects(old->object);
	scene->anti_a = old->anti_a;
	scene->cam = old->cam;
	scene->pd = old->pd;
	scene->shininess = old->shininess;
	scene->record = old->record;
	scene->spec = old->spec;
	scene->theta = old->theta;
	scene->curr_object = old->curr_object;
	return (scene);
}
