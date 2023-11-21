/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:18:33 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/21 19:23:03 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//POLICE
# define RED "\033[31m"
# define END "\033[0m"

//HOOK
# define KEY_PRESS 2
# define ON_DESTROY 17

# define FOV 90

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"

enum	e_type
{
	ARGC,
	PARSING,
	MALLOC,
};

enum	e_errors
{
	EXTENSION,
	NOFNAME,
	OPEN,
	TEXTURES,
};

enum	e_boolean
{
	TRUE,
	FALSE,
};

struct	s_mlx_data
{
	void	*mlx;
	void	*window;
};

typedef struct s_textures
{
	int		no_flag;
	char	*no_path;
	int		so_flag;
	char	*so_path;
	int		we_flag;
	char	*we_path;
	int		ea_flag;
	char	*ea_path;
}		t_textures;

typedef	struct	s_colors
{
	int	f_flag;
	int	f_colors[3];
	int	c_flag;
	int	c_colors[3];
}		t_colors;

typedef struct	s_parser
{
	int			fd;
	char		*line;
	char		**map;
	t_textures	textures;
	t_colors	*colors;
}		t_parser;

typedef	struct s_data
{
	struct s_mlx_data	mlx;
	int					screen_res[2];
}		t_data;

//ERROR
void	print_error(int type, int error);

//MLX
int		start_mlx(t_data *data);

//INITIALIZATION
void	initialize_parser(t_parser *parser);

//PARSING
void	parsing(char *file_path, char *file_name);
void	get_file_content(t_parser *parser, char *file_path);

//FREE
void	free_data(t_data *data);
void	free_parser(t_parser *parser);

//EXIT
int		exit_prog(t_data *data);

#endif
