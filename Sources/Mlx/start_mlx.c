/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:11 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/14 00:16:46 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_ratio(t_data *data, int minimap_x, int minimap_y)
{
	int	ratio_x;
	int	ratio_y;

	ratio_x = data->screen_res[0] / minimap_x;
	ratio_y = data->screen_res[1] / minimap_y;
	return ((ratio_x + ratio_y) / 2);
}

static void	get_screen_res(t_data *data)
{
	int	x_res;
	int	y_res;

	mlx_get_screen_size(data->mlx.mlx, &x_res, &y_res);
	if (x_res < SCREEN_RES_X || y_res < SCREEN_RES_Y)
	{
		data->screen_res[0] = x_res;
		data->screen_res[1] = y_res;
	}
	else
	{
		data->screen_res[0] = SCREEN_RES_X;
		data->screen_res[1] = SCREEN_RES_Y;
	}
}

int	start_mlx(t_data *data)
{
	int	sprite;

	get_screen_res(data);
	data->screen_res[0] = SCREEN_RES_X;
	data->screen_res[1] = SCREEN_RES_Y;
	data->mlx.window = mlx_new_window(data->mlx.mlx, data->screen_res[0],
			data->screen_res[1], "cub3D");
	if (!data->mlx.window)
		return (0);
	data->mlx.frame.img = mlx_new_image(data->mlx.mlx, data->screen_res[0], data->screen_res[1]);
	data->mlx.frame.addr = mlx_get_data_addr(data->mlx.frame.img, &data->mlx.frame.bpp, &data->mlx.frame.line_length, &data->mlx.frame.endian);
	data->minimap_ratio = get_ratio(data, ft_strlen(data->map[0]), ft_arr_size(data->map)) / 8;
	initstart_ennemy(data);
	data->saved_data.x_pos = data->player.x_pos;
	data->saved_data.y_pos = data->player.y_pos;
	data->saved_data.angle = data->player.angle;
	data->saved_data.ennemy_pos[0] = data->ennemy.pos[0];
	data->saved_data.ennemy_pos[1] = data->ennemy.pos[1];
	mlx_loop_hook(data->mlx.mlx, execution, data);
	data->ghost.img = mlx_xpm_file_to_image(data->mlx.mlx, "Textures/ghost.xpm", &sprite, &sprite);
	if (!data->ghost.img)
		printf("KO texture\n");
	data->zbuffer = NULL;
	mlx_mouse_hook(data->mlx.window, mouse_hook, data);
	mlx_hook(data->mlx.window, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.window, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->mlx.window, ON_DESTROY, 0L, exit_prog, data);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window, &data->mouse_pos[0], &data->mouse_pos[1]);
	mlx_mouse_hide(data->mlx.mlx, data->mlx.window);
	mlx_loop(data->mlx.mlx);
	return (1);
}
