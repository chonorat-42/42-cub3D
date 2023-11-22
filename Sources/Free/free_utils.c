/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:01:03 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/22 19:04:46 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_maplst(t_maplst *lst)
{
	t_maplst	*temp;

	temp = lst;
	while (lst)
	{
		if (lst->content)
			free(lst->content);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
	lst = NULL;
}
