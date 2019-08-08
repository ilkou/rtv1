/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:54:03 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/06 18:55:43 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

void		ft_free_objects(t_object *obj)
{
	if (obj != NULL && obj->next != NULL)
		ft_free_objects(obj->next);
	if (obj->name != NULL)
	    free(obj->name);
	if (obj != NULL)
	    free(obj);
}

void		ft_free_lights(t_light *light)
{
	if (light != NULL && light->next != NULL)
		ft_free_lights(light->next);
	if (light != NULL)
	    free(light);
}

t_light		*ft_copy_lights(t_light *old)
{
	t_light		*new;

	if (!old || !(new = (struct s_l*)malloc(sizeof(struct s_l))))
		return (NULL);
	new->intensity = old->intensity;
	new->pos = old->pos;
	new->col = old->col;
	new->dir = old->dir;
	new->intensity = old->intensity;
	new->next = NULL;
	if (old->next)
		new->next = ft_copy_lights(old->next);
	return (new);
}

t_object	*ft_copy_objects(t_object *old, int one_object)
{
	t_object	*new;

	if (!old || !(new = (struct s_o*)malloc(sizeof(struct s_o))))
		return (NULL);
	new->pos = old->pos;
	new->col = old->col;
	new->hit = old->hit;
	new->size = old->size;
	new->rot = old->rot;
	new->type = old->type;
	new->name = ft_strdup(old->name);
	new->next = NULL;
	if (old->next && !one_object)
		new->next = ft_copy_objects(old->next, one_object);
	return (new);
}

t_scene		*ft_copy_scene(t_scene *old)
{
	t_scene		*scene;

	if (!old || !(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		return (NULL);
	scene->light = ft_copy_lights(old->light);
	scene->object = ft_copy_objects(old->object, 0);
	scene->anti_a = old->anti_a;
	scene->cam = old->cam;
	scene->coef_spec = old->coef_spec;
	scene->brillance = old->brillance;
	scene->spec = old->spec;
	scene->theta = old->theta;
	scene->curr_object = ft_copy_objects(old->curr_object, 1);
	return (scene);
}
