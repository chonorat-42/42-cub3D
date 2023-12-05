/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:04:48 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/05 16:35:21 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_tex_img(t_tex_img *tex_img)
{
	tex_img->no_img = NULL;
	tex_img->so_img = NULL;
	tex_img->ea_img = NULL;
	tex_img->we_img = NULL;
}

void	init_data(t_data *data)
{
	data->mlx.mlx = NULL;
	data->mlx.window = NULL;
	data->screen_res[0] = 0;
	data->screen_res[1] = 0;
	data->player.dir = 0;
	data->player.x_pos = 0;
	data->player.y_pos = 0;
	data->player.move.f_move = 0;
	data->player.move.b_move = 0;
	data->player.move.l_move = 0;
	data->player.move.r_move = 0;
	data->player.move.sprint = 0;
	data->map = NULL;
	init_tex_img(&data->tex_img);
	data->mlx.mlx = mlx_init();
	data->ennemy.mask = NULL;
	if (!data->mlx.mlx)
		return (free_data(data), print_error(MALLOC, 0), exit(1));
}
