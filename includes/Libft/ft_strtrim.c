/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:15:02 by marvin            #+#    #+#             */
/*   Updated: 2025/10/18 13:15:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s1len;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	s1len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[s1len]))
		s1len--;
	s1len = s1len - i + 1;
	str = ft_substr(s1, i, s1len);
	if (!str)
		return (NULL);
	return (str);
}
