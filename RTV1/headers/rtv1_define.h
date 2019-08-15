/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:27:36 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/15 19:28:10 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_DEFINE_H
# define RTV1_DEFINE_H

# define PS p->scene
# define MSP mlx_string_put

# define FRAME 10
# define MENU_BAR 150
# define IMG_WIDTH 1000.0
# define IMG_HEIGHT (IMG_WIDTH / 2)
# define WIN_WIDTH (IMG_WIDTH + (2 * FRAME))
# define WIN_HEIGHT (IMG_HEIGHT + FRAME + MENU_BAR)

# define COND_SLCT1(x) (x > FRAME && x < IMG_WIDTH + FRAME)
# define COND_SLCT2(y) (y > MENU_BAR && y < IMG_HEIGHT + MENU_BAR)
# define COND_SELECT(x, y) (COND_SLCT1(x) && COND_SLCT2(y))

# define BG_COL_1 0xAAAAAA
# define BG_COL_2 0xB8B8B8
# define BG_COL_3 0x3E3E3d
# define BG_COL_4 0x797978

# define COL1 0x333333
# define COL2 0x000000

# define COND_BG1(row) (row > FRAME && row < MENU_BAR - FRAME)
# define COND_BG2(col) (col > FRAME && col < WIN_WIDTH - FRAME)
# define BG_COND(row, col) (COND_BG1(row) && COND_BG2(col))
# define RWH(row) (row < WIN_HEIGHT - FRAME)
# define CWW(col) (col < WIN_WIDTH - FRAME)
# define BG_COND1(row, col) (col == FRAME && row > MENU_BAR && RWH(row))
# define BG_COND2(row, col) (row == MENU_BAR && col > FRAME && CWW(col))

# define NBTHREAD 4

# define DEFAULT -2147483648.0

# define FR(x, y) ({free(x); y;})
# define C_S "\t\"Object\": \"Sphere\""
# define C_P "\t\"Object\": \"Plane\""
# define C_CO "\t\"Object\": \"Cone\""
# define C_CY "\t\"Object\": \"Cylinder\""
# define COL_TYPE(x) (x < 0.0 || x > 1.0)

# define END(x) (x[0][ft_strlen(*x) - 1])

# define MLX_KEY_LEFT 123
# define MLX_KEY_RIGHT 124
# define MLX_KEY_UP 126
# define MLX_KEY_DOWN 125
# define MLX_KEY_ESC 53
# define MLX_KEY_ENTER 36
# define MLX_KEY_D 2
# define MLX_KEY_B 11
# define MLX_KEY_S 1
# define MLX_KEY_X 7
# define MLX_KEY_Y 16
# define MLX_KEY_Z 6
# define MLX_KEY_A 0
# define MLX_KEY_O 31
# define MLX_KEY_C 8
# define MLX_KEY_L 37
# define MLX_KEY_MINUS 78
# define MLX_KEY_PLUS 69

# define THE_ABS(x) { x = x > 0 ? x : -x; }
# define RGB(x) (int)(255.99 * x)
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))

#endif
