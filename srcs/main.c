/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 22:37:07 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/16 11:43:48 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

void	ft_free_exit(char *display, int err, t_ptr **p)
{
	char	*msg;

	msg = ft_strjoin(err ? "error: " : "", display);
	ft_putstr(msg);
	free(msg);
	ft_free_objects((*p)->scene->object);
	ft_free_lights((*p)->scene->light);
	free((*p)->scene);
	free(*p);
	exit(0);
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

void	ft_parser(t_ptr *p, char *chemin)
{
	int		fd;
	int		check;
	char	*scene;
	
	fd = open(chemin, O_RDONLY, !O_DIRECTORY);
	
	if ((fd = open(chemin, O_RDONLY)) == -1)
		ft_free_exit(ft_strjoin(chemin, " : No such file\n"), 1, &p);
	if (open(chemin, O_DIRECTORY) != -1)
		ft_free_exit(ft_strjoin(chemin, " : must be a file\n"), 1, &p);
	scene = get_full_text(fd);
	close(fd);
	check = ft_check_brackets(scene);
	free(scene);
	if (check < 2)
		ft_free_exit("brackets\n", 1, &p);
	fd = open(chemin, O_RDONLY);
	ft_get_data(p, fd);
	ft_check_data(p);
}

int		main(int argc, char **argv)
{
	t_ptr	*p;

	if (!(p = (struct s_ptr*)malloc(sizeof(struct s_ptr))))
		return (0);
	p->scene = ft_init_scene();
	if (argc == 2)
		ft_parser(p, argv[1]);
	else
		ft_free_exit("usage: ./rtv1 scene_file\ncheck ./scenes\n", 0, &p);
	ft_init(p);
	ft_create_window(p);
	ft_create_image(p);
	ft_background(p);
	ft_draw(p);
	mlx_hook(p->win, 17, 0, ft_close, p);
	mlx_hook(p->win, 2, 0, ft_deal_key, p);
	mlx_hook(p->win, 4, 0, ft_mouse_press, p);
	mlx_loop(p->mlx);
	return (0);
}
