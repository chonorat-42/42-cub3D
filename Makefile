# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 13:10:41 by chonorat          #+#    #+#              #
#    Updated: 2023/12/08 12:26:29 by pgouasmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLOR
_GREEN = \033[92m
_YELLOW = \033[33m
_RED = \033[31m

#POLICE
_END = \033[0m
_BOLD = \033[1m

OS = $(shell uname)

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -IIncludes -ggdb3
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L ./minilibx-linux -Imlx_linux -lXext -lX11 -lm -lz
RM = @rm -rf
CC = @cc
DIR = @mkdir -p
PRINT = @echo
HEADER = Includes/$(NAME).h
LIBFT = Libft/libft.a
MAKE_LIBFT = @make -C Libft
CLEAN_LIBFT = @make clean -C Libft
FCLEAN_LIBFT = @make fclean -C Libft
MLX = minilibx-linux/libmlx.a
MAKE_MLX = @make -C minilibx-linux
CLEAN_MLX = @make clean -C minilibx-linux
NORM = @norminette Includes Sources | awk '$$NF!="OK!" {print "$(_RED)" $$0 "\033[0;0m"}'
FILES = cub3D\
		Errors/print_error\
		Mlx/start_mlx\
		Mlx/key_hook\
		Mlx/pixel_to_frame\
		Initialization/parser_init\
		Initialization/data_init\
		Parsing/parsing\
		Parsing/get_file_content\
		Print/print_cub\
		Print/print_minimap\
		Print/print_player\
		Raycasting/raycasting\
		Raycasting/print_column\
		Raycasting/get_fog\
		Move/move_player\
		Move/get_move\
		Move/rotate_cam\
		Parsing/get_file_utils\
		Parsing/get_textures\
		Parsing/get_colors\
		Parsing/trgb\
		Parsing/get_map\
		Parsing/get_map_utils\
		Parsing/map_parsing\
		Parsing/get_player_dir\
		Parsing/fill_map\
		Parsing/check_borders\
		Parsing/get_player_position\
		Parsing/check_separation\
		Parsing/flood_fill_algorithm\
		Parsing/flood_fill_utils\
		Free/free_data\
		Free/free_parser\
		Free/free_utils\
		Exit/exit_prog\
		Prints/prints\
		Pathfinding/pathfinding\
		Pathfinding/ennemy_update\
		Pathfinding/pathfinding_utils\
		Pathfinding/evaluate_options\
		Pathfinding/evaluate_north\
		Pathfinding/evaluate_south\
		Pathfinding/compare_options

OBJS = $(addsuffix .o, $(addprefix Objects/, $(FILES)))

$(NAME): $(OBJS) | $(LIBFT) $(MLX)
ifeq ($(OS),Linux)
	$(PRINT) "\n${_BOLD}Waiting for norminette...${_END}"
	$(NORM)
	$(PRINT) "${_BOLD}Norminette done.${_END}"
	$(PRINT) "\n${_YELLOW}Making $(NAME)...${_END}"
	$(CC) -O2 $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	$(PRINT) "${_BOLD}${_GREEN}$(NAME) done.\a${_END}"
else
	$(PRINT) "$(OS)" > .OS
endif

Objects/%.o: Sources/%.c Makefile $(HEADER)
ifeq ($(OS),Linux)
	$(DIR) Objects
	$(DIR) Objects/Errors Objects/Mlx Objects/Parsing Objects/Initialization Objects/Raycasting Objects/Pathfinding
	$(DIR) Objects/Free Objects/Exit Objects/Print Objects/Prints Objects/Move
	$(PRINT) "Compiling ${_BOLD}$<$(_END)..."
	$(CC) -O2 -c $(CFLAGS) $< -o $@
else
	$(PRINT) "$(OS)" > .OS
endif

$(LIBFT):
ifeq ($(OS),Linux)
	$(PRINT) "\n${_YELLOW}Checking Libft...${_END}"
	$(MAKE_LIBFT)
else
	$(PRINT) "\nThis $(NAME) was made for Linux only.\a\n"
endif

$(MLX):
ifeq ($(OS),Linux)
	$(PRINT) "\n${_YELLOW}Waiting for MLX...${_END}"
	$(MAKE_MLX)
	$(PRINT) "${_BOLD}${_GREEN}MLX done.${_END}\n"
else
	$(PRINT) "$(OS)" > .OS
endif

all: $(NAME)

clean:
	$(CLEAN_LIBFT)
	$(PRINT) "\n${_RED}Cleaning MLX...${_END}"
	$(CLEAN_MLX)
	$(PRINT) "${_GREEN}MLX cleaned.${_END}"
	$(PRINT) "\n${_BOLD}Cleaning Objects...${_END}"
	$(RM) .OS
	$(RM) $(OBJS)
	$(PRINT) "${_BOLD}${_GREEN}Objects cleaned.\a${_END}"

fclean:
	$(FCLEAN_LIBFT)
	$(PRINT) "\n${_RED}Cleaning MLX...${_END}"
	$(CLEAN_MLX)
	$(PRINT) "${_GREEN}MLX cleaned.${_END}"
	$(PRINT) "\n${_RED}Cleaning Objects...${_END}"
	$(RM) $(OBJS)
	$(PRINT) "${_RED}Deleting Objects directory...${_END}"
	$(RM) Objects
	$(PRINT) "${_RED}Deleting $(NAME)...${_END}"
	$(RM) $(NAME)
	$(RM) .OS
	$(PRINT) "${_GREEN}Objects cleaned.${_END}"
	$(PRINT) "${_GREEN}Objects directory deleted.${_END}"
	$(PRINT) "${_GREEN}$(NAME) deleted.\a\n${_END}"

re: fclean all

norminette:
	$(PRINT) "\n${_BOLD}Waiting for norminette...${_END}"
	$(NORM)
	$(PRINT) "${_BOLD}Norminette done.${_END}"

.PHONY: all clean fclean re norminette $(LIBFT) $(MLX)
