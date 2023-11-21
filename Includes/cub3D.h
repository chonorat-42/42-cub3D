/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:18:33 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/21 15:30:55 by chonorat         ###   ########.fr       */
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

enum	e_errors
{
	ARGC,
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

typedef	struct s_data
{
	struct s_mlx_data	mlx;
	int					screen_res[2];
}		t_data;

//ERROR
void	print_error(int type, int error);

//MLX
int		start_mlx(t_data *data);

//FREE
void	free_data(t_data *data);

//EXIT
int		exit_prog(t_data *data);

#endif
