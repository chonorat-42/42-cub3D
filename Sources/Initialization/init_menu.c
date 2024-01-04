/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:01:15 by chonorat          #+#    #+#             */
/*   Updated: 2024/01/04 13:02:54 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_pause(t_data *data)
{
	data->pause_menu.on_resume = 0;
	data->pause_menu.on_options = 0;
	data->pause_menu.on_exit = 0;
	data->pause_menu.on_back = 0;
	data->pause_menu.on_difficulty = 0;
	data->pause_menu.on_minimap = 0;
	data->pause_menu.on_fog = 0;
	data->pause_menu.on_retry = 0;
	data->pause_menu.on_mouse_sens = 0;
}

void	init_options(t_data *data)
{
	data->minimap_toggle = 1;
	data->difficulty = HARD;
	data->fog_setting = HIGH;
	data->fog_density = 1.5;
	data->mouse_sensibility = 0.003;
	data->mouse_settings = 3;
}
