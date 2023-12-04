/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:18:33 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/04 14:55:38 by chonorat         ###   ########lyon.fr   */
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
# define ON_MOUSE_MOVE 6

# define R_MOVE 100
# define B_MOVE 115
# define L_MOVE 97
# define F_MOVE 119
# define L_CAM 65361
# define R_CAM 65363
# define ESC 65307
# define MAJ 65505

# define S_PLAYER_SPEED 0.05
# define PLAYER_SPEED 0.025
# define CAM_SPEED 0.05
# define MOUSE_SPEED 0.005

# define SCREEN_RES_X 1920
# define SCREEN_RES_Y 1080

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
	EMPTYL,
	SEP,
};

enum	e_boolean
{
	FALSE,
	TRUE,
};

struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
};

struct	s_mlx_data
{
	void			*mlx;
	void			*window;
	struct s_img	frame;
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
	int	l_cam;
	int	r_cam;
	int	sprint;
};

struct	s_raycast
{
	double			x_cam;
	double			xpos_ray;
	double			ypos_ray;
	double			xdir_ray;
	double			ydir_ray;
	int				x_map;
	int				y_map;
	double			delta_dist_x;
	double			delta_dist_y;
	int				x_step;
	int				y_step;
	double			side_dist_x;
	double			side_dist_y;
	double			pwall_dist;
	int				height;
	int				width;
	int				wall_side;
	int				wall_hit;
	struct s_img	wall;
	double			wall_hit_point;
};

struct	s_player
{
	double			x_pos;
	double			y_pos;
	double			x_dir;
	double			y_dir;
	double			x_plane;
	double			y_plane;
	double			angle;
	struct s_move	move;
};

typedef struct s_flood
{
	size_t			y;
	size_t			x;
	struct s_flood *next;
}		t_flood;

typedef struct s_data
{
	struct s_mlx_data	mlx;
	int					screen_res[2];
	char				**map;
	int					minimap_ratio;
	int					mouse_pos[2];
	int					reset_mouse;
	struct s_player		player;
	struct s_parser		parser;
	struct s_tex_img	tex_img;
}		t_data;

//ERROR
void	print_error(int type, int error);

//MLX
int		start_mlx(t_data *data);
void	pixel_to_frame(t_data *data, int x, int y, int color);

//HOOK
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);

//INITIALIZATION
void	init_data(t_data *data);
void	initialize_parser(t_parser *parser);
void	init_raycast(struct s_raycast *data_rc);

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
void	get_player_dir(t_data *data, long long i, long long j);
void	fill_map(t_data *data, t_parser *parser);
int		check_borders(char **map);
void	get_player_position(t_data *data);
int		is_map_separated(t_data *data, char **map);
void	iterative_flood(t_data *data, char **map);
void	first_position(t_data *data, t_flood **flood, char **map);
int		add_to_flood(t_flood **flood, size_t j, size_t i);
void 	free_flood(t_flood **flood);


//PRINT
int		print_cub(t_data *data);
void	print_minimap(t_data *data);
void	print_player(t_data *data, double radius, int color);
void	raycasting(t_data *data, struct s_raycast *data_rc);
int		wall_hit(t_data *data, int pos_x, int pos_y);

//MOVE
void	get_move(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_cam(t_data *data);

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
