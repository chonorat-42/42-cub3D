/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrinset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:46:49 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/27 14:50:52 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_isstrinset(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_ischarinset(str[i], set))
			return (1);
		i++;
	}
	return (0);
}
