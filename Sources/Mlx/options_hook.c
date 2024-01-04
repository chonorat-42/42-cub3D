/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:08:15 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/17 16:12:06 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_pause(t_data *data)
{
	data->mouse_enabled++;
	data->mouse_enabled %= 2;
	data->pause_menu.in_pause++;
	data->pause_menu.in_pause %= 2;
	data->pause_menu.in_options = 0;
	if (data->pause_menu.in_pause)
		mlx_mouse_show(data->mlx.mlx, data->mlx.window);
	else if (!data->pause_menu.in_pause)
		mlx_mouse_hide(data->mlx.mlx, data->mlx.window);
}

static void	change_difficulty(t_data *data)
{
	if (data->difficulty == IMPOSSIBLE)
	{
		data->difficulty = EASY;
		data->ennemy.speed = 0.0125;
	}
	else
	{
		data->difficulty++;
		data->ennemy.speed += 0.0125;
	}
}

static void	change_fog(t_data *data)
{
	if (data->fog_setting == VERY_HIGH)
	{
		data->fog_setting = LOW;
		data->fog_density = 0.5;
	}
	else
	{
		data->fog_setting++;
		data->fog_density += 0.5;
	}
}

static void	change_mouse(t_data *data)
{
	if (data->mouse_settings == 5)
	{
		data->mouse_settings = 1;
		data->mouse_sensibility = 0.001;
	}
	else
	{
		data->mouse_settings++;
		data->mouse_sensibility += 0.001;
	}
}

void	options_hook(t_data *data)
{
	if (data->pause_menu.on_back)
		data->pause_menu.in_options = 0;
	if (data->pause_menu.on_difficulty)
		change_difficulty(data);
	if (data->pause_menu.on_fog)
		change_fog(data);
	if (data->pause_menu.on_minimap)
	{
		data->minimap_toggle++;
		data->minimap_toggle %= 2;
	}
	if (data->pause_menu.on_mouse_sens)
		change_mouse(data);
}
