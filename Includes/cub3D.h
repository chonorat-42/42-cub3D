/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:18:33 by chonorat          #+#    #+#             */
/*   Updated: 2024/01/04 14:06:18 by chonorat         ###   ########lyon.fr   */
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
# define TAB 65289
# define F1 65470

# define L_MOUSE 1

//FONT
# define STD_FONT "-*-*-*-*-*-*-24-230-*-*-*-*-iso8859-*"
# define HEAD_FONT "-*-*-*-*-*-*-56-230-*-*-*-*-iso8859-*"

//SPEED
# define S_PLAYER_SPEED 0.05
# define PLAYER_SPEED 0.025
# define CAM_SPEED 0.05

# define MAX 1000000

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
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
	DPX,
	TEXDIM,
};

enum	e_fog
{
	LOW,
	MEDIUM,
	HIGH,
	VERY_HIGH,
};

enum	e_difficulty
{
	EASY,
	NORMAL,
	HARD,
	IMPOSSIBLE,
};

enum	e_directions
{
	N,
	S,
	E,
	W,
	NE,
	NW,
	SE,
	SW,
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

typedef struct s_trgb
{
	int	ceiling;
	int	floor;
}		t_trgb;

typedef struct s_tex_img
{
	void	*no_img;
	void	*so_img;
	void	*ea_img;
	void	*we_img;
	void	*no_exit_img;
	void	*so_exit_img;
	void	*ea_exit_img;
	void	*we_exit_img;
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

typedef struct s_exit
{
	double			x;
	double			y;
	size_t			nbr;
	struct s_exit	*next;
}		t_exit;

typedef struct s_path
{
	double			coor[2];
	struct s_path	*next;
	struct s_path	*head;
}		t_path;

typedef struct s_ennemy
{
	int				pres;
	double			speed;
	double			d_pos[2];
	double			target[2];
	int				pos[2];
	int				last;
	char			**dup_map;
	struct s_path	*path;
	size_t			len;
	size_t			height;
	char			c;

}			t_ennemy;

struct s_print_rc
{
	int	h_line;
	int	start;
	int	end;
	int	color;
};

struct	s_sprite
{
	double			distance;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			x_transform;
	double			y_transform;
	int				screen_x;
	int				sprite_h;
	int				sprite_w;
	int				start_y;
	int				end_y;
	int				start_x;
	int				end_x;
	int				tex_x;
	int				tex_y;
	int				color;
	int				d;
	int				y;
	struct s_img	sprite;
};

struct	s_raycast
{
	double				x_cam;
	double				xpos_ray;
	double				ypos_ray;
	double				xdir_ray;
	double				ydir_ray;
	int					x_map;
	int					y_map;
	double				delta_dist_x;
	double				delta_dist_y;
	int					x_step;
	int					y_step;
	double				side_dist_x;
	double				side_dist_y;
	double				pwall_dist;
	int					height;
	int					width;
	int					wall_side;
	int					wall_hit;
	struct s_img		wall;
	double				wall_hit_point;
	struct s_print_rc	print;
	struct s_sprite		ennemy;
};

struct	s_player
{
	double			x_pos;
	double			y_pos;
	int				l_pos[2];
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
	struct s_flood	*next;
}		t_flood;

struct s_pause
{
	int	in_pause;
	int	on_resume;
	int	on_options;
	int	on_exit;
	int	in_options;
	int	on_difficulty;
	int	on_minimap;
	int	on_fog;
	int	on_mouse_sens;
	int	on_back;
	int	on_retry;
	int	in_escape;
	int	in_death;
};

struct s_save_data
{
	double			x_pos;
	double			y_pos;
	double			angle;
	int				ennemy_pos[2];
};

typedef struct s_data
{
	char				**map;
	int					screen_res[2];
	int					minimap_ratio;
	int					mouse_pos[2];
	int					reset_mouse;
	int					mouse_enabled;
	int					difficulty;
	int					minimap_toggle;
	int					fog_setting;
	double				fog_density;
	double				*zbuffer;
	double				mouse_sensibility;
	int					mouse_settings;
	struct s_mlx_data	mlx;
	struct s_ennemy		ennemy;
	struct s_exit		*exit;
	struct s_img		ghost;
	struct s_player		player;
	struct s_parser		parser;
	struct s_tex_img	tex_img;
	struct s_trgb		colors;
	struct s_pause		pause_menu;
	struct s_save_data	saved_data;
}		t_data;

//ERROR
void	print_error(int type, int error);

//MLX
int		start_mlx(t_data *data);
void	pixel_to_frame(t_data *data, int x, int y, int color);

//HOOK
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		mouse_hook(int mousekey, int x, int y, t_data *data);

//INITIALIZATION
void	init_data(t_data *data);
void	initialize_parser(t_parser *parser);
void	init_raycast(t_data *data, struct s_raycast *data_rc);
void	initstart_ennemy(t_data *data);
void	init_pause(t_data *data);
void	init_options(t_data *data);

//PARSING
void	parsing(t_data *data, char *file_path, char *file_name);
void	get_file_content(t_parser *parser, char *file_path);
int		check_parsing_flags(t_textures textures, t_colors colors);
void	line_found(t_parser *parser, size_t *line_count);
void	parse_id(t_parser *parser, char *id, size_t	*i);
void	get_textures(t_parser *parser);
void	open_north_and_south_textures(t_data *data, t_parser *parser);
void	open_east_and_west_textures(t_data *data, t_parser *parser);
void	get_colors(t_parser *parser, char *id, size_t *i);
void	get_trgb(t_data *data, t_parser *parser);
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
void	free_flood(t_flood **flood);
void	get_ennemy_position(t_data *data);
void	get_exit_position(t_data *data);

//PATHFINDING
void	pathfinding(t_data *data, char **map, int y, int x);
size_t	difference(int a, int b);
double	double_difference(double a, double b);
void	clean_mask(int **mask, size_t height, size_t len);
void	free_ull(unsigned long long **arr, int line);
void	fill_mask(int **mask, char **map);
void	init_ennemy(t_data *data, t_ennemy *ennemy, char **map);
int		update_path(t_data *data, t_path **path, int c, int *pos);
size_t	smallest(unsigned long long **arr, t_ennemy ennemy, int y, int x);
void	evaluate_options(t_data *data, unsigned long long **arr, int y, int x);
void	evaluate_north(t_data *data, unsigned long long **arr, int y, int x);
void	evaluate_south(t_data *data, unsigned long long **arr, int y, int x);

//EXECUTION
int		execution(t_data *data);
void	pause_menu(t_data *data);
void	options_hook(t_data *data);
void	set_pause(t_data *data);
void	show_options_text(t_data *data);
void	show_difficulty(t_data *data);
void	show_fog(t_data *data);
void	show_minimap(t_data *data);
void	show_mouse_sens(t_data *data);
void	death_screen(t_data *data);
void	escape_screen(t_data *data);

//PRINT
void	print_minimap(t_data *data);
void	print_player(t_data *data, double radius, int color);
int		wall_hit(t_data *data, int pos_x, int pos_y);

//RAYCASTING
void	raycasting(t_data *data);
int		get_fog(int color, double fog_intensity, double distance);
void	print_column(t_data *data, struct s_raycast *data_rc, int x);
void	get_sprite(t_data *data, struct s_raycast *data_rc);

//MOVE
void	get_move(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_cam(t_data *data);
void	move_ennemy(t_data *data);

//FREE
void	free_data(t_data *data);
void	free_parser(t_parser *parser);
void	free_maplst(t_dlst *lst);
void	free_path(t_path **path);

//EXIT
int		exit_prog(t_data *data);

//PRINTS
void	print_arr(char **arr);
void	print_dlst(t_dlst *lst);

#endif
