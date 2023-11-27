/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:41:41 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 19:02:48 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_tex_img(t_tex_img *data, void *mlx)
{
	if (data->no_img)
		mlx_destroy_image(mlx, data->no_img);
	if (data->so_img)
		mlx_destroy_image(mlx, data->so_img);
	if (data->ea_img)
		mlx_destroy_image(mlx, data->ea_img);
	if (data->we_img)
		mlx_destroy_image(mlx, data->we_img);
}

void	free_data(t_data *data)
{
	free_parser(&data->parser);
	ft_free_arr(data->map);
	if (data->mlx.mlx)
	{
		free_tex_img(&data->tex_img, data->mlx.mlx);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
}
