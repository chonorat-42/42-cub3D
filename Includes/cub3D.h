/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:18:33 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/28 15:05:52 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//POLICE
# define RED "\033[31m"
# define END "\033[0m"

//HOOK
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define ON_DESTROY 17
# define R_MOVE 100
# define B_MOVE 115
# define L_MOVE 97
# define F_MOVE 119
# define ESC 65307
# define MAJ 65505

# define FOV 70

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
	COLORS,
	NOMAP,
	TEXOP,
	NOP,
	DPP,
	BORD,
	SPACEB,
	UNKCHAR,
};

enum	e_boolean
{
	FALSE,
	TRUE,
};

struct	s_mlx_data
{
	void	*mlx;
	void	*window;
};

typedef struct s_dlst
{
	char			*content;
	struct s_dlst	*next;
	struct s_dlst	*prev;
}		t_dlst;

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

typedef struct s_colors
{
	int	f_flag;
	int	f_colors[3];
	int	c_flag;
	int	c_colors[3];
}		t_colors;

typedef struct s_tex_img
{
	void	*no_img;
	void	*so_img;
	void	*ea_img;
	void	*we_img;
}		t_tex_img;

typedef struct s_parser
{
	int			fd;
	char		*line;
	char		**map;
	t_textures	textures;
	t_colors	colors;
}		t_parser;

struct	s_move
{
	int	f_move;
	int	b_move;
	int	l_move;
	int	r_move;
	int	sprint;
};

struct	s_player
{
	double			dir;
	double			x_pos;
	double			y_pos;
	struct s_move	move;
};

typedef struct s_data
{
	struct s_mlx_data	mlx;
	int					screen_res[2];
	char				**map;
	int					minimap_ratio;
	struct s_player		player;
	struct s_parser		parser;
	struct s_tex_img	tex_img;
}		t_data;

//ERROR
void	print_error(int type, int error);

//MLX
int		start_mlx(t_data *data);

//INITIALIZATION
void	init_data(t_data *data);
void	initialize_parser(t_parser *parser);

//PARSING
void	parsing(t_data *data, char *file_path, char *file_name);
void	get_file_content(t_parser *parser, char *file_path);
int		check_parsing_flags(t_textures textures, t_colors colors);
void	line_found(t_parser *parser, size_t *line_count);
void	parse_id(t_parser *parser, char *id, size_t	*i);
void	get_textures_and_colors(t_parser *parser);
int		open_textures(t_data *data, t_parser *parser);
void	get_colors(t_parser *parser, char *id, size_t *i);
void	get_map(t_parser *parser);
void	map_parser(t_data *data, t_parser *parser);
size_t	maplst_size(t_dlst *lst);
int		initialize_dlst_content(t_dlst *new, char *str);
int		add_to_maplst(t_dlst **lst, char *str);
size_t	maplst_size(t_dlst *lst);
void	delete_middle_node(t_dlst **temp);
void	fill_map(t_data *data, t_parser *parser);
int		check_borders(char **map);
void	get_player_position(t_data *data);

//PRINT
int		print_cub(t_data *data);
void	print_minimap(t_data *data);
void	print_player(t_data *data, double radius, int color);

//MOVE
void	move_player(t_data *data);

//FREE
void	free_data(t_data *data);
void	free_parser(t_parser *parser);
void	free_maplst(t_dlst *lst);

//EXIT
int		exit_prog(t_data *data);

//PRINTS
void	print_arr(char **arr);
void	print_dlst(t_dlst *lst);

#endif
