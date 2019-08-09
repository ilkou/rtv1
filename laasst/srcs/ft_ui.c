/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:41:09 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/07 19:50:33 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/rtv1.h"

int			ft_bg_col(int bg, int x, int y)
{
	if (bg && ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0)))
		return (BG_COL_1);
	else if (bg && !((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0)))
		return (BG_COL_2);
	else if (!bg && ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0)))
		return (BG_COL_3);
	else
		return (BG_COL_4);
}

char		*ft_ctoa(t_color c)
{
	char	*ret;
	char	*r;
	char	*g;
	char	*b;

	r = ft_dtoa(c.r);
	g = ft_dtoa(c.g);
	b = ft_dtoa(c.b);
	ret = ft_mystrjoin(r, " ", 0);
	ret = ft_mystrjoin(ret, g, 2);
	ret = ft_mystrjoin(ret, " ", 0);
	ret = ft_mystrjoin(ret, b, 2);
	return (ret);
}

char		*ft_vtoa(t_vector v)
{
	char	*ret;
	char	*v1;
	char	*v2;
	char	*v3;

	v1 = ft_dtoa(v.v1);
	v2 = ft_dtoa(v.v2);
	v3 = ft_dtoa(v.v3);
	ret = ft_mystrjoin(v1, " ", 0);
	ret = ft_mystrjoin(ret, v2, 2);
	ret = ft_mystrjoin(ret, " ", 0);
	ret = ft_mystrjoin(ret, v3, 2);
	return (ret);
}

void        ft_object_selected(t_ptr *p)
{
    char	*size;
    char	*col;
    char	*pos;
    char    *rot;

    size = ft_dtoa(PS->curr_object->size);
    col = ft_ctoa(PS->curr_object->col);
    pos = ft_vtoa(PS->curr_object->pos);
    rot = ft_vtoa(PS->curr_object->rot);
    MSP(p->mlx, p->win, FRAME + 110, FRAME + 10, COL2, PS->curr_object->name);
    MSP(p->mlx, p->win, FRAME + 110, FRAME + 30, COL2, pos);
    MSP(p->mlx, p->win, FRAME + 110, FRAME + 50, COL2, rot);
    MSP(p->mlx, p->win, FRAME + 110, FRAME + 70, COL2, col);
    MSP(p->mlx, p->win, FRAME + 110, FRAME + 90, COL2, size);
    free(size);
    free(col);
    free(pos);
    free(rot);
}

void        ft_display_properties(t_ptr *p)
{
    char *cam;
    char *theta;
    char *anti_a;
    char *spec;
    char *brillance;

    cam = ft_vtoa(PS->cam.origin);
    theta = ft_dtoa(PS->theta);
    anti_a = ft_dtoa(PS->anti_a);
    spec = PS->spec ? ft_strdup("On") : ft_strdup("Off");
    brillance = ft_dtoa(PS->brillance);
    MSP(p->mlx, p->win, FRAME + 510, FRAME + 10, COL2, cam);
    MSP(p->mlx, p->win, FRAME + 510, FRAME + 30, COL2, theta);
    MSP(p->mlx, p->win, FRAME + 510, FRAME + 50, COL2, anti_a);
    MSP(p->mlx, p->win, FRAME + 510, FRAME + 70, COL2, spec);
    MSP(p->mlx, p->win, FRAME + 510, FRAME + 90, COL2, brillance);
    free(cam);
    free(theta);
    free(anti_a);
    free(spec);
    free(brillance);
}
void        ft_display_moves(t_ptr *p)
{
    if (p->inc_dec == 1)
    {
        MSP(p->mlx, p->win, FRAME + 710, FRAME + 10, COL2, "Increase/");
        MSP(p->mlx, p->win, FRAME + 800, FRAME + 10, COL1, "Decrease");
    } else
    {
        MSP(p->mlx, p->win, FRAME + 710, FRAME + 10, COL1, "Increase/");
        MSP(p->mlx, p->win, FRAME + 800, FRAME + 10, COL2, "Decrease");
    }
    MSP(p->mlx, p->win, FRAME + 640, FRAME + 30, COL1,
            "[X|Y|Z]: Rotation about x/y/z axis");
    MSP(p->mlx, p->win, FRAME + 640, FRAME + 50, COL1, "[<X>|^Yv|-Z+]: Move");
    MSP(p->mlx, p->win, FRAME + 640, FRAME + 70, COL1, "[C]: Camera ");
    (p->cam_slct) ?
    MSP(p->mlx, p->win, FRAME + 760, FRAME + 70, COL2, "Selected") :
    MSP(p->mlx, p->win, FRAME + 760, FRAME + 70, COL1, "Unselected");
    MSP(p->mlx, p->win, FRAME + 640, FRAME + 90, COL1, "[L]: Lights ");
    (p->light_slct) ?
    MSP(p->mlx, p->win, FRAME + 760, FRAME + 90, COL2, "Selected") :
    MSP(p->mlx, p->win, FRAME + 760, FRAME + 90, COL1, "Unselected");
}

void		ft_menu_bar(t_ptr *p)
{
	MSP(p->mlx, p->win, FRAME + 10, FRAME + 10, COL1, "Selected: ");
	MSP(p->mlx, p->win, FRAME + 10, FRAME + 30, COL1, "Position: ");
    MSP(p->mlx, p->win, FRAME + 10, FRAME + 50, COL1, "Rotation: ");
	MSP(p->mlx, p->win, FRAME + 10, FRAME + 70, COL1, "Color: ");
	MSP(p->mlx, p->win, FRAME + 10, FRAME + 90, COL1, "Size: ");
    MSP(p->mlx, p->win, FRAME + 310, FRAME + 10, COL1, "Cam Position: ");
    MSP(p->mlx, p->win, FRAME + 310, FRAME + 30, COL1, "[O]Rotation Angle: ");
    MSP(p->mlx, p->win, FRAME + 310, FRAME + 50, COL1, "[A]AntiAliasing: ");
    MSP(p->mlx, p->win, FRAME + 310, FRAME + 70, COL1, "[S]Specularity: ");
    MSP(p->mlx, p->win, FRAME + 310, FRAME + 90, COL1, "[B]Brillance: ");
    MSP(p->mlx, p->win, FRAME + 640, FRAME + 10, COL1, "[Enter]");
    ft_display_properties(p);
    ft_display_moves(p);
	if (PS->curr_object == NULL)
        MSP(p->mlx, p->win, FRAME + 110, FRAME + 10, COL2, "No Object");
    else
        ft_object_selected(p);
}

void		ft_background(t_ptr *p)
{
    int		col;
    int		row;

    row = 0;
    while (row < WIN_HEIGHT)
    {
        col = 0;
        while (col < WIN_WIDTH)
        {
            if (BG_COND(row, col))
                mlx_pixel_put(p->mlx, p->win, col, row, ft_bg_col(1, row, col));
            else
                mlx_pixel_put(p->mlx, p->win, col, row, ft_bg_col(0, row, col));
            col = BG_COND1(row, col) ? WIN_WIDTH - FRAME : col + 1;
        }
        row = BG_COND2(row, col) ? WIN_HEIGHT - FRAME : row + 1;
    }
    ft_menu_bar(p);
}