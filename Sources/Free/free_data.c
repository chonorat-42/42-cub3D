/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:41:41 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/06 18:44:51 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_ennemy(t_ennemy *ennemy)
{
	size_t	j;

	if (!ennemy->mask)
		return ;
	j = 0;
	while (j < ennemy->height)
	{
		free(ennemy->mask[j]);
		j++;
	}
	free(ennemy->mask);
}

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

static void	free_path(t_path **path)
{
	t_path	*temp;

	temp = *path;
	while (*path)
	{
		temp = *path;
		*path = (*path)->next;
		free(temp);
	}
}

void	free_data(t_data *data)
{
	free_parser(&data->parser);
	free_ennemy(&data->ennemy);
	free_path(&data->ennemy.path);
	if (data->map)
		ft_free_arr(data->map);
	if (data->mlx.mlx)
	{
		free_tex_img(&data->tex_img, data->mlx.mlx);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
}
