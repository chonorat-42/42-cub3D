/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:41:41 by chonorat          #+#    #+#             */
/*   Updated: 2024/01/04 15:06:19 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_path(t_path **path)
{
	t_path	*temp;

	if (!(*path))
		return ;
	*path = (*path)->head;
	while (*path)
	{
		temp = *path;
		*path = (*path)->next;
		free(temp);
	}
	*path = NULL;
}

static void	free_ennemy(t_ennemy *ennemy)
{
	ft_free_arr(ennemy->dup_map);
	free_path(&ennemy->path);
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
	if (data->ea_exit_img)
		mlx_destroy_image(mlx, data->ea_exit_img);
	if (data->we_exit_img)
		mlx_destroy_image(mlx, data->we_exit_img);
	if (data->no_exit_img)
		mlx_destroy_image(mlx, data->no_exit_img);
	if (data->so_exit_img)
		mlx_destroy_image(mlx, data->so_exit_img);
}

void	free_exit(t_exit **exit)
{
	t_exit	*temp;

	if (!*exit)
		return ;
	while (*exit)
	{
		temp = *exit;
		*exit = (*exit)->next;
		free(temp);
	}
	*exit = NULL;
}

void	free_data(t_data *data)
{
	free_parser(&data->parser);
	free_ennemy(&data->ennemy);
	free_exit(&data->exit);
	if (data->map)
		ft_free_arr(data->map);
	if (data->mlx.frame.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.frame.img);
	if (data->ghost.img)
		mlx_destroy_image(data->mlx.mlx, data->ghost.img);
	if (data->mlx.mlx)
	{
		free_tex_img(&data->tex_img, data->mlx.mlx);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
	if (data->zbuffer)
		free(data->zbuffer);
}
