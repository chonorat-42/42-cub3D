/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:16:12 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/23 13:16:53 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_isstrws(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isws(str[i]))
			return (0);
		i++;
	}
	return (1);
}
