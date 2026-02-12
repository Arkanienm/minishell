/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:48:00 by amurtas           #+#    #+#             */
/*   Updated: 2025/10/27 11:13:44 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	cs;

	cs = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cs)
			return ((char *)s + i);
		i++;
	}
	if (cs == 0 && !s[i])
		return ((char *)s + i);
	return (NULL);
}
