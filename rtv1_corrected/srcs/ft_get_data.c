/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:30:52 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 17:32:02 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

void			ft_add_camera(t_ptr *p, int fd, char **line, int t)
{
	t_camera		cam;

	(t > 0) ? ft_free_exit("wrong camera number\n", 1, &p) : (t++);
	if (ft_strcmp(*line, "\t\"Camera\":") && FR(*line, 1))
		ft_free_exit("Camera syntax\n", 1, &p);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_free_exit("Camera syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"lookfrom\": \""
					, 15) || END(line) != '"'))
		ft_free_exit("Camera syntax - lookfrom\n", 1, &p);
	cam.origin = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"lookat\": \""
					, 13) || END(line) != '"'))
		ft_free_exit("Camera syntax - lookat\n", 1, &p);
	cam.lookat = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"fov\": \""
					, 10) || END(line) != '"'))
		ft_free_exit("Camera syntax - fov\n", 1, &p);
	cam.fov = ft_linetod(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_free_exit("Camera syntax - near to }\n", 1, &p);
	p->scene->cam = ft_init_camera(cam.origin, cam.lookat, cam.fov);
}

void			ft_get_object(t_ptr *p, t_object *obj, int fd, char **line)
{
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_free_exit("Object syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"position\": \""
					, 15) || END(line) != '"'))
		ft_free_exit("Object syntax - 1st param position\n", 1, &p);
	obj->pos = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"rotation\": \""
					, 15) || END(line) != '"'))
		ft_free_exit("Object syntax - 2nd param rotation\n", 1, &p);
	obj->rot = ft_normalize(ft_linetorot(p, line, 1));
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line,
					"\t\t\"translation\": \"", 18) || END(line) != '"'))
		ft_free_exit("Object syntax - 3rd param translation\n", 1, &p);
	obj->pos = ft_add(obj->pos, ft_linetovec(p, line, 1));
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"color\": \""
					, 12) || END(line) != '"'))
		ft_free_exit("Object syntax - 4th param color\n", 1, &p);
	obj->col = ft_linetocol(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"size\": \""
					, 11) || END(line) != '"'))
		ft_free_exit("Object syntax - 5th param size\n", 1, &p);
	obj->size = ft_linetod(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_free_exit("Object syntax - near to }\n", 1, &p);
}

void			ft_add_object(t_ptr *p, int fd, char **line, int t)
{
	t_object		*obj;
	t_object		*tmp;

	if (!(obj = (struct s_o*)malloc(sizeof(struct s_o))) && t < 0)
		ft_free_exit("cannot allocate\n", 1, &p);
	tmp = p->scene->object;
	if (ft_strcmp(*line, C_S) && ft_strcmp(*line, C_CO) && ft_strcmp(*line, C_P)
			&& ft_strcmp(*line, C_CY) && FR(*line, 1))
		ft_free_exit("object syntax - undefined object\n", 1, &p);
	if (!ft_strcmp(*line, C_S) && (obj->hit = ft_hit_sphere))
		obj->name = ft_strdup("SPHERE");
	else if (!ft_strcmp(*line, C_CY) && (obj->hit = ft_hit_cylinder))
		obj->name = ft_strdup("CYLINDER");
	else if (!ft_strcmp(*line, C_CO) && (obj->hit = ft_hit_cone))
		obj->name = ft_strdup("CONE");
	else if (!ft_strcmp(*line, C_P) && (obj->hit = ft_hit_plane))
		obj->name = ft_strdup("PLANE");
	ft_get_object(p, obj, fd, line);
	p->scene->object = obj;
	obj->next = tmp;
}

void			ft_add_light(t_ptr *p, int fd, char **line)
{
	t_light			*light[2];

	if (!(light[0] = (struct s_l*)malloc(sizeof(struct s_l))))
		ft_free_exit("cannot allocate\n", 1, &p);
	light[1] = p->scene->light;
	if (ft_strcmp(*line, "\t\"Light\":") && FR(*line, 1))
		ft_free_exit("Light syntax\n", 1, &p);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_free_exit("Light syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"position\": \""
					, 15) || END(line) != '"') && FR(*line, 1))
		ft_free_exit("Light syntax - 1st param position\n", 1, &p);
	light[0]->pos = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"color\": \""
					, 12) || END(line) != '"') && FR(*line, 1))
		ft_free_exit("Light syntax - 2nd param color\n", 1, &p);
	light[0]->col = ft_linetocol(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line,
					"\t\t\"intensity\": \"", 16) || END(line) != '"'))
		ft_free_exit("Light syntax - 3d param intensity\n", 1, &p);
	light[0]->intensity = ft_clamping(ft_linetod(p, line, 1));
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_free_exit("Light syntax - near to }\n", 1, &p);
	p->scene->light = light[0];
	light[0]->next = light[1];
}

void			ft_get_data(t_ptr *p, int fd)
{
	static int		cam_nbr;
	static int		obj_nbr;
	char			*line;

	get_next_line(fd, &line);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp(line, "\t\"Camera\":", 10))
			ft_add_camera(p, fd, &line, cam_nbr++);
		else if (!ft_strncmp(line, "\t\"Object\": ", 11))
			ft_add_object(p, fd, &line, obj_nbr++);
		else if (!ft_strncmp(line, "\t\"Light\":", 9))
			ft_add_light(p, fd, &line);
		else if (!ft_strncmp(line, "]", 1))
			break ;
		else
			ft_free_exit("unexpected data\n", 1, &p);
		free(line);
	}
	if (cam_nbr == 0 || obj_nbr == 0)
		ft_free_exit("data missing - minimum \"1camera,1object\"\n", 1, &p);
}
