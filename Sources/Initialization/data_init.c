/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:04:48 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/01/04 13:03:35 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_tex_img(t_data *data, t_tex_img *tex_img)
{
	tex_img->no_img = NULL;
	tex_img->so_img = NULL;
	tex_img->ea_img = NULL;
	tex_img->we_img = NULL;
	tex_img->no_exit_img = NULL;
	tex_img->so_exit_img = NULL;
	tex_img->ea_exit_img = NULL;
	tex_img->we_exit_img = NULL;
	data->ghost.img = NULL;
	data->mlx.frame.img = NULL;
}

static void	init_player(t_data *data)
{
	data->player.x_dir = 0;
	data->player.y_dir = 0;
	data->player.x_pos = 0;
	data->player.y_pos = 0;
	data->player.x_plane = 0;
	data->player.y_plane = 0;
	data->player.move.f_move = 0;
	data->player.move.b_move = 0;
	data->player.move.l_move = 0;
	data->player.move.r_move = 0;
	data->player.move.l_cam = 0;
	data->player.move.r_cam = 0;
	data->player.move.sprint = 0;
}

void	init_raycast(t_data *data, struct s_raycast *data_rc)
{
	data_rc->delta_dist_x = 0;
	data_rc->delta_dist_y = 0;
	data_rc->pwall_dist = 0;
	data_rc->side_dist_x = 0;
	data_rc->side_dist_y = 0;
	data_rc->x_cam = 0;
	data_rc->x_map = 0;
	data_rc->y_map = 0;
	data_rc->xpos_ray = 0;
	data_rc->ypos_ray = 0;
	data_rc->xdir_ray = 0;
	data_rc->ydir_ray = 0;
	data_rc->x_step = 0;
	data_rc->y_step = 0;
	data_rc->wall_side = 0;
	data_rc->wall_hit = 0;
	data_rc->wall_hit_point = 0;
	data_rc->wall.img = NULL;
	data->zbuffer = NULL;
}

void	init_data(t_data *data)
{
	data->mlx.mlx = NULL;
	data->mlx.window = NULL;
	data->screen_res[0] = 0;
	data->screen_res[1] = 0;
	data->mouse_pos[0] = 0;
	data->mouse_pos[1] = 0;
	data->reset_mouse = 0;
	data->mouse_enabled = 1;
	data->map = NULL;
	data->pause_menu.in_pause = 0;
	data->pause_menu.in_options = 0;
	data->pause_menu.in_escape = 0;
	data->pause_menu.in_death = 0;
	data->zbuffer = NULL;
	init_pause(data);
	init_options(data);
	init_player(data);
	init_tex_img(data, &data->tex_img);
	initstart_ennemy(data);
	data->exit = NULL;
	data->mlx.mlx = NULL;
}
