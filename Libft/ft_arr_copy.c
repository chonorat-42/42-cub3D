/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:58:47 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/10/06 11:58:47 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	**ft_arr_copy(char **envp)
{
	char	**arr;
	size_t	j;
	size_t	k;
	size_t	arr_size;

	arr_size = ft_arr_size(envp);
	arr = malloc(sizeof(char *) * (arr_size + 1));
	if (!arr)
		return (NULL);
	j = 0;
	while (j < arr_size)
	{
		arr[j] = ft_strdup(envp[j]);
		if (!arr[j])
		{
			k = -1;
			while (++k < j)
				free(arr[k]);
			return (NULL);
		}
		j++;
	}
	arr[arr_size] = NULL;
	return (arr);
}
