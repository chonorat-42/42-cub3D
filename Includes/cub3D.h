/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:18:33 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/21 12:41:37 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//POLICE
# define RED "\033[31m"
# define END "\033[0m"

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

//ERROR
void	print_error(int type, int error);

#endif
