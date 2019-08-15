/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:27:23 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 17:12:02 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_check_brackets(char *s)
{
	int			b;
	int			i;

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

t_vector	ft_linetovec(t_ptr *p, char **line, int free_it)
{
	t_vector	ret;
	char		**each;
	char		*str;

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
	return (ret);
}

t_color		ft_linetocol(t_ptr *p, char **line, int free_it)
{
	t_color		ret;
	char		**each;
	char		*str;

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

double		ft_linetod(t_ptr *p, char **line, int free_it)
{
	double		ret;
	char		**each;
	char		*str;

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
	return (ret);
}

void		ft_check_data(t_ptr *p)
{
	t_object *tmp;

	tmp = p->scene->object;
	if (p->scene->cam.fov < 0.0 || p->scene->cam.fov > 180.0)
		ft_free_exit("wrong field of view value\n", 1, &p);
	while (tmp)
	{
		if (tmp->size < 0.001 && tmp->hit != ft_hit_plane)
			ft_free_exit("wrong size detected\n", 1, &p);
		if (COL_TYPE(tmp->col.r) || COL_TYPE(tmp->col.g)
				|| COL_TYPE(tmp->col.b))
			ft_free_exit("wrong color format detected\n", 1, &p);
		tmp = tmp->next;
	}
}
