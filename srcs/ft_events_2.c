/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 18:48:29 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 18:53:54 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_close(t_ptr *p)
{
	mlx_destroy_image(p->mlx, p->img);
	mlx_destroy_window(p->mlx, p->win);
	free(p->bpp);
	free(p->size);
	free(p->endian);
	ft_free_exit("", 0, &p);
	return (0);
}

int			ft_delete_object(t_object **list, t_object **to_delete)
{
	t_object	*temp;
	t_object	*next;

	temp = *list;
	if (temp == *to_delete)
	{
		*list = temp->next;
		free(temp);
		*to_delete = NULL;
		return (1);
	}
	while (temp)
	{
		if (temp->next && temp->next == *to_delete)
			break ;
		temp = temp->next;
	}
	next = temp->next->next;
	free(temp->next);
	temp->next = next;
	*to_delete = NULL;
	return (2);
}

void		ft_select_obj(t_ptr *p, int col, int row)
{
	t_ray		r;

	r = ft_get_ray(&PS->cam, col, row);
	if (ft_hit(PS->object, r, I(0.0001, DBL_MAX), &PS->record))
		PS->curr_object = PS->record.curr_obj;
	else
		PS->curr_object = NULL;
}

void		ft_selected_event(int key, t_ptr *p)
{
	t_object	*tmp;

	tmp = PS->object;
	while (tmp && PS->curr_object != NULL)
	{
		if (tmp == PS->curr_object)
			break ;
		tmp = tmp->next;
	}
	if (key == MLX_KEY_X && PS->curr_object != NULL)
		tmp->rot = ft_rot_x(tmp->rot, p->inc_dec * DEG_TO_RAD(PS->theta));
	if (key == MLX_KEY_Y && PS->curr_object != NULL)
		tmp->rot = ft_rot_y(tmp->rot, p->inc_dec * DEG_TO_RAD(PS->theta));
	if (key == MLX_KEY_Z && PS->curr_object != NULL)
		tmp->rot = ft_rot_z(tmp->rot, p->inc_dec * DEG_TO_RAD(PS->theta));
	if (key == MLX_KEY_S)
		PS->spec = PS->spec ? 0 : 1;
	if (key == MLX_KEY_B)
		PS->shininess = p->inc_dec > 0 ? PS->shininess + 5 : PS->shininess - 5;
	PS->shininess = PS->shininess <= 5 ? 5.0 : PS->shininess;
	if (key == MLX_KEY_A && !(p->inc_dec < 0 && PS->anti_a == 1.5))
		PS->anti_a = p->inc_dec > 0 ? PS->anti_a * 2.0 : PS->anti_a / 2.0;
}

int			ft_menu_event(int key, t_ptr *p)
{
	if (key == MLX_KEY_O && p->inc_dec == 1)
		PS->theta = PS->theta + 2.5 < 180.0 ? PS->theta + 2.5 : -180.0;
	if (key == MLX_KEY_O && p->inc_dec == -1)
		PS->theta = PS->theta - 2.5 > -180.0 ? PS->theta - 2.5 : 180.0;
	if (key == MLX_KEY_ENTER)
		p->inc_dec = p->inc_dec == 1 ? -1 : 1;
	return (key == MLX_KEY_O || key == MLX_KEY_ENTER);
}
