/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:25:30 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/15 16:15:43 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_textures(t_data *data, t_parser *parser)
{
	int	width;
	int	height;

	data->tex_img.no_img = mlx_xpm_file_to_image(data->mlx.mlx,
			parser->textures.no_path, &width, &height);
	if (data->tex_img.no_img == NULL)
		return (free_data(data), print_error(PARSING, TEXOP), exit(1));

	printf("width = %d, height = %d\n", width, height);

	if (width != 256 || height != 256)
		return (free_data(data), print_error(PARSING, TEXDIM), exit(1));
	data->tex_img.so_img = mlx_xpm_file_to_image(data->mlx.mlx,
			parser->textures.so_path, &width, &height);
	if (data->tex_img.so_img == NULL)
		return (free_data(data), print_error(PARSING, TEXOP), exit(1));
	if (width != 256 || height != 256)
		return (free_data(data), print_error(PARSING, TEXDIM), exit(1));
	data->tex_img.ea_img = mlx_xpm_file_to_image(data->mlx.mlx,
			parser->textures.ea_path, &width, &height);
	if (data->tex_img.ea_img == NULL)
		return (free_data(data), print_error(PARSING, TEXOP), exit(1));
	if (width != 256 || height != 256)
		return (free_data(data), print_error(PARSING, TEXDIM), exit(1));
	data->tex_img.we_img = mlx_xpm_file_to_image(data->mlx.mlx,
			parser->textures.we_path, &width, &height);
	if (data->tex_img.we_img == NULL)
		return (free_data(data), print_error(PARSING, TEXOP), exit(1));
	if (width != 256 || height != 256)
		return (free_data(data), print_error(PARSING, TEXDIM), exit(1));
}

static void	parse_line(t_parser *parser, char *line)
{
	size_t	i;
	size_t	j;
	char	*id;

	i = 0;
	while (line[i] && ft_isws(line[i]))
		i++;
	j = i;
	while (line[i] && !ft_isws(line[i]))
		i++;
	id = ft_substr(line, j, i - j);
	if (!id)
		return (free_parser(parser), print_error(MALLOC, 0), exit(1));
	parse_id(parser, id, &i);
	free(id);
}

void	line_found(t_parser *parser, size_t *line_count)
{
	(*line_count)++;
	parse_line(parser, parser->line);
	free(parser->line);
	parser->line = NULL;
}

int	check_parsing_flags(t_textures textures, t_colors colors)
{
	if (textures.ea_flag != 1 || textures.no_flag != 1
		|| textures.so_flag != 1 || textures.we_flag != 1)
		return (0);
	if (colors.f_flag != 1 || colors.c_flag != 1)
		return (0);
	return (1);
}
