/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:03:58 by amurtas           #+#    #+#             */
/*   Updated: 2025/10/27 11:39:35 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (to_find[0] == '\0')
		return (((char *)str));
	while (str[i] && i < len)
	{
		k = i;
		while (str[k] == to_find[j] && k < len)
		{
			if (!(to_find[j + 1] != '\0' && k < len))
				return (&((char *)str)[0 + i]);
			j++;
			k++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
