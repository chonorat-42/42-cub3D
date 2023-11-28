/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstronlyset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:09:32 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/27 18:13:25 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_isstronlyset(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_ischarinset(str[i], set))
			return (0);
		i++;
	}
	return (1);
}
