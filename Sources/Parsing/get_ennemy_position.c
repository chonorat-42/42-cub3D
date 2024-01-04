/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ennemy_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:39:45 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/01/04 12:49:20 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ennemy_present(char **map, t_data *data)
{
	size_t	j;
	size_t	i;

	j = 0;
	data->ennemy.pres = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (ft_ischarinset(map[j][i], "X"))
			{
				data->ennemy.pres++;
				data->ennemy.pos[0] = j;
				data->ennemy.pos[1] = i;
			}
			i++;
		}
		j++;
	}
	if (!data->ennemy.pres)
		return (0);
	if (data->ennemy.pres > 1)
		return (print_error(PARSING, DPX), free_data(data), 0);
	return (1);
}

void	get_ennemy_position(t_data *data)
{
	int	height;
	int	width;

	if (!ennemy_present(data->parser.map, data))
		return ;
	data->ghost.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"Textures/ghost.xpm", &height, &width);
	if (!data->ghost.img)
		return (print_error(TEXOP, 0), free_data(data), exit(1));
	if (height != 256 || width != 256)
		return (print_error(TEXDIM, 0), free_data(data), exit(1));
}

static int	add_exit(t_exit **lst, size_t j, size_t i)
{
	t_exit	*new;
	t_exit	*temp;

	new = malloc(sizeof(*new));
	if (!new)
		return (print_error(MALLOC, 0), 1);
	new->next = NULL;
	new->y = j + 0.5;
	new->x = i + 0.5;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

static void	load_exit_images(t_data *data)
{
	int	height;
	int	width;

	data->tex_img.no_exit_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"Textures/NO_EXIT.xpm", &height, &width);
	if (!data->tex_img.no_exit_img)
		return (print_error(PARSING, TEXOP), free_data(data), exit(1));
	data->tex_img.so_exit_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"Textures/SO_EXIT.xpm", &height, &width);
	if (!data->tex_img.so_exit_img)
		return (print_error(PARSING, TEXOP), free_data(data), exit(1));
	data->tex_img.we_exit_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"Textures/WE_EXIT.xpm", &height, &width);
	if (!data->tex_img.we_exit_img)
		return (print_error(PARSING, TEXOP), free_data(data), exit(1));
	data->tex_img.ea_exit_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"Textures/EA_EXIT.xpm", &height, &width);
	if (!data->tex_img.ea_exit_img)
		return (print_error(PARSING, TEXOP), free_data(data), exit(1));
}

void	get_exit_position(t_data *data)
{
	size_t	j;
	size_t	i;

	data->exit = NULL;
	j = 0;
	while (data->parser.map[j])
	{
		i = 0;
		while (data->parser.map[j][i])
		{
			if (data->parser.map[j][i] == 'V')
			{
				if (add_exit(&data->exit, j, i))
					return (free_data(data), exit(1));
			}
			i++;
		}
		j++;
	}
	if (data->exit)
		load_exit_images(data);
}
