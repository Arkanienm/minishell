/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:26:36 by amurtas           #+#    #+#             */
/*   Updated: 2025/10/27 12:06:08 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_size;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (size == 0 && !dst)
		return (src_size);
	dest_size = ft_strlen(dst);
	if (dest_size >= size)
		return (size + src_size);
	while (src[i] != '\0' && (dest_size + i + 1) < size)
	{
		dst[i + dest_size] = src[i];
		i++;
	}
	dst[i + dest_size] = '\0';
	return (dest_size + src_size);
}
