/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:05:47 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/06 21:21:29 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/rtv1.h"

char	*get_full_text(const int fd)
{
	char *text;
	char *tmp;
	int ret;
	int sum;

	sum = 0;
	text = (char*)malloc(BUFF_SIZE + 1);
	while ((ret = read(fd, &text[sum], BUFF_SIZE)))
	{
		sum += ret;
		text[sum] = '\0';
		tmp = ft_strdup(text);
		free(text);
		text = (char*)malloc(sum + BUFF_SIZE + 1);
		ft_strcpy(text, tmp);
		free(tmp);
	}
	text[sum] = '\0';
	return (text);
}

void	ft_free_exit(char *display, int err, t_ptr **p)
{
	char *msg;

	msg = ft_strjoin(err ? "error: " : "", display);
	ft_putstr(msg);
	free(msg);
	ft_free_objects((*p)->scene->object);
	ft_free_lights((*p)->scene->light);
	free((*p)->scene);
	free(*p);
	exit(0);
}

static int	ft_check_brackets(char *s)
{
	int b;
	int i;

	i = 1;
	b = 0;
	while (s[i])
	{
		if (s[i] == '}')
			return (0);
		if (s[i] == '{')
		{
			b++;
			while (s[i])
			{
				i++;
				if (s[i] == '{')
					return (0);
				if (s[i] == '}')
					break ;
			}
		}
		i++;
	}
	return (s[0] && s[0] == '[' && s[i - 2] && s[i - 2] == ']' ? b : 0);
}

void ft_print_vector(t_vector v)
{
	ft_putstr(ft_dtoa(v.v1));
	ft_putstr(" ");
	ft_putstr(ft_dtoa(v.v2));
	ft_putstr(" ");
	ft_putstr(ft_dtoa(v.v3));
	ft_putstr(" ");
}
void ft_print_color(t_color v)
{
	ft_putstr(ft_dtoa(v.r));
	ft_putstr(" ");
	ft_putstr(ft_dtoa(v.g));
	ft_putstr(" ");
	ft_putstr(ft_dtoa(v.b));
	ft_putstr(" ");
}
void ft_free_twodim(char **to_free)
{
	int i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}
int ft_twodimlen(char **twodim)
{
	int s;

	s = 0;
	while (*twodim++)
		s++;
	return (s);
}
t_vector ft_linetovec(t_ptr *p, char **line, int free_it)
{
	t_vector ret;
	char **each;
	char *str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 3)
		ft_free_exit("must be three values for such data\n", 1, &p);
	ret.v1 = ft_atod(each[0]);
	ret.v2 = ft_atod(each[1]);
	ret.v3 = ft_atod(each[2]);
	ft_free_twodim(each);
	//ft_print_vector(ret);
	return (ret);
}
t_color ft_linetocol(t_ptr *p, char **line, int free_it)
{
	t_color ret;
	char **each;
	char *str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 3)
		ft_free_exit("must be three values for such data\n", 1, &p);
	ret.r = ft_atod(each[0]);
	ret.g = ft_atod(each[1]);
	ret.b = ft_atod(each[2]);
	ft_free_twodim(each);
	return (ret);
}
double ft_linetod(t_ptr *p, char **line, int free_it)
{
	double ret;
	char **each;
	char *str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 1)
		ft_free_exit("must be one value for such data\n", 1, &p);
	ret = ft_atod(each[0]);
	ft_free_twodim(each);
	//ft_putstr(ft_dtoa(ret));
	return (ret);
}

# define FR(x, y) ({free(x); y;})
# define C_S "\t\"Object\": \"Sphere\""
# define C_P "\t\"Object\": \"Plane\""
# define C_CO "\t\"Object\": \"Cone\""
# define C_CY "\t\"Object\": \"Cylinder\""

void ft_add_camera(t_ptr *p, int fd, char **line, int t)
{
	t_vector cam[2];
	double		fov;

	(t == 1337 || t > 0) ? ft_free_exit("wrong camera number\n", 1, &p) : (t++);
	if (ft_strcmp(*line, "\t\"Camera\":") && FR(*line, 1))
		ft_free_exit("Camera syntax\n", 1, &p);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_free_exit("Camera syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"lookfrom\": \"", 15) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Camera syntax - lookfrom\n", 1, &p);
	cam[0] = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"lookat\": \"", 13) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Camera syntax - lookat\n", 1, &p);
	cam[1] = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"fov\": \"", 10) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Camera syntax - fov\n", 1, &p);
	fov = ft_linetod(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_free_exit("Camera syntax - near to }\n", 1, &p);
	p->scene->cam = ft_init_camera(cam[0], cam[1], fov);
}
void	ft_get_object(t_ptr *p, t_object *obj, int fd, char **line)
{
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && FR(*line, 1))
		ft_free_exit("Object syntax - near to {\n", 1, &p);
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"position\": \"", 15) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Object syntax - 1st param position\n", 1, &p);
	obj->pos = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"rotation\": \"", 15) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Object syntax - 2nd param rotation\n", 1, &p);
	obj->rot = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"translation\": \"", 18) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Object syntax - 3rd param translation\n", 1, &p);
	obj->pos = ft_add(obj->pos, ft_linetovec(p, line, 1));
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"color\": \"", 12) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Object syntax - 4th param color\n", 1, &p);
	obj->col = ft_linetocol(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strncmp(*line,
		"\t\t\"size\": \"", 11) || line[0][ft_strlen(*line) - 1] != '"')
		ft_free_exit("Object syntax - 5th param size\n", 1, &p);
	obj->size = ft_linetod(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && FR(*line, 1))
		ft_free_exit("Object syntax - near to }\n", 1, &p);
}

void ft_add_object(t_ptr *p, int fd, char **line, int t)
{
	t_object   *obj;
	t_object	*tmp;

    if (t < 0 || !(obj = (struct s_o*)malloc(sizeof(struct s_o))))
        ft_free_exit("cannot allocate the object\n", 1, &p);
    tmp = p->scene->object;
    if (ft_strcmp(*line, C_S) && ft_strcmp(*line, C_CO) && ft_strcmp(*line, C_P)
    	&& ft_strcmp(*line, C_CY) && FR(*line, 1))
		ft_free_exit("object syntax - undefined object\n", 1, &p);
	if (!ft_strcmp(*line, C_S) && (obj->hit = ft_hit_sphere)
		&& (obj->name = ft_strdup("SPHERE")));
	else if (!ft_strcmp(*line, C_CY) && (obj->hit = ft_hit_cylinder)
		&& (obj->name = ft_strdup("CYLINDER")));
	else if (!ft_strcmp(*line, C_CO) && (obj->hit = ft_hit_cone)
		&& (obj->name = ft_strdup("CONE")));
	else if (!ft_strcmp(*line, C_P) && (obj->hit = ft_hit_plane)
		&& (obj->name = ft_strdup("PLANE")));
	ft_get_object(p, obj, fd, line);
	p->scene->object = obj;
	obj->next = tmp;
}
void ft_add_light(t_ptr *p, int fd, char **line)
{
}

void	ft_get_data(t_ptr *p, int fd)
{
	static int cam_nbr;
	static int obj_nbr;
	char *line;

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
			break;
		else
			ft_free_exit("unexpected data\n", 1, &p);
		free(line);
	}
	if (cam_nbr == 0 || obj_nbr == 0)
		ft_free_exit("data missing - minimum \"1camera,1object\"\n", 1, &p);
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
t_scene     *ft_init_scene()
{
    t_scene     *scene;

    if (!(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
        return (NULL);
    scene->anti_a = 3.0;
    scene->object = NULL;
    scene->light = NULL;
    scene->coef_spec = 4.0;
    scene->brillance = 30.0;
    scene->spec = 1;
    scene->theta = 45.0 / 2.0;
    scene->curr_object = NULL;
    return (scene);
}
void ft_print_data(t_ptr *p)
{
	t_object *tmp;

	tmp = p->scene->object;
	while (tmp)
	{
		if (tmp->hit == ft_hit_cylinder)
			ft_putstr("cylinder\n");
		if (tmp->hit == ft_hit_cone)
			ft_putstr("cone\n");
		if (tmp->hit == ft_hit_sphere)
			ft_putstr("sphere\n");
		if (tmp->hit == ft_hit_plane)
			ft_putstr("plane\n");
		ft_putstr("position: ");
		ft_print_vector(tmp->pos);
		ft_putstr("\nrotation: ");
		ft_print_vector(tmp->rot);
		ft_putstr("\ncolor: ");
		ft_print_color(tmp->col);
		ft_putstr("\nsize: ");
		ft_putstr(ft_dtoa(tmp->size));
		ft_putendl("\nnext object: \n");
		tmp = tmp->next;
	}
}
# define COL_TYPE(x) (x < 0.0 || x > 1.0)
void	ft_check_data(t_ptr *p)
{
	t_object *tmp;

	tmp = p->scene->object;
	if (p->scene->cam.fov < 0.0 || p->scene->cam.fov > 180.0)
		ft_free_exit("wrong field of view value\n", 1, &p);
	while (tmp)
	{
		if (tmp->size < 0.001)
			ft_free_exit("wrong size detected\n", 1, &p);
		if (COL_TYPE(tmp->col.r) || COL_TYPE(tmp->col.g) || COL_TYPE(tmp->col.b))
			ft_free_exit("wrong color format detected\n", 1, &p);
		tmp = tmp->next;
	}
}
int	ft_read_file(t_ptr *p, char *chemin)
{
	int		fd;
	int		check;
	char	*scene;

	if ((fd = open(chemin, O_RDONLY)) == -1)
		return (0);
	scene = get_full_text(fd);
	close(fd);
	check = ft_check_brackets(scene);
	free(scene);
	if (check < 2)
		ft_free_exit("brackets\n", 1, &p);
	fd = open(chemin, O_RDONLY);
	p->scene = ft_init_scene();
	ft_get_data(p, fd);
	ft_print_data(p);
	ft_check_data(p);
	return (check);
}

int	main(int argc, char **argv)
{
	t_ptr *p;

	p = (struct s_ptr*)malloc(sizeof(struct s_ptr));
	if (argc == 2)
		printf("%d\n", ft_read_file(p, argv[1])/* ? "good" : "bad"*/);
	return (0);
}
