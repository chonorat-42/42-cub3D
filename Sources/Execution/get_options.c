/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:33:26 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/17 15:55:55 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	show_difficulty(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 100,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "Difficulty :");
	if (data->difficulty == EASY)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 60,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "EASY");
	else if (data->difficulty == NORMAL)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 60,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "NORMAL");
	else if (data->difficulty == HARD)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 60,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "HARD");
	else if (data->difficulty == IMPOSSIBLE)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 60,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "IMPOSSIBLE");
}

void	show_fog(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 100,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "Fog density :");
	if (data->fog_setting == LOW)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 70,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, "LOW");
	else if (data->fog_setting == MEDIUM)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 70,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, "MEDIUM");
	else if (data->fog_setting == HIGH)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 70,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, "HIGH");
	else if (data->fog_setting == VERY_HIGH)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 70,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, "VERY HIGH");
}

void	show_minimap(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 100,
		(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, "Minimap :");
	if (data->minimap_toggle)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 20,
			(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, "ENABLED");
	else if (!data->minimap_toggle)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 20,
			(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, "DISABLED");
}

void	show_mouse_sens(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 100, (data->screen_res[1] >> 1) + 55,
		(int)0xFFFFFF, "Mouse sensibility :");
	if (data->mouse_settings == 1)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "1");
	else if (data->mouse_settings == 2)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "2");
	else if (data->mouse_settings == 3)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "3");
	else if (data->mouse_settings == 4)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "4");
	else if (data->mouse_settings == 5)
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "5");
}
