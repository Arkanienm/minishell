/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:45:46 by amurtas           #+#    #+#             */
/*   Updated: 2025/10/27 12:14:29 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			word++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word);
}

static void	*ft_free_all(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (str[i] == NULL)
		{
			while (n > 0)
			{
				n--;
				free(str[n]);
			}
			free(str);
			return (NULL);
		}
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		len;

	len = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof (char *) * (ft_count_word(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		len = 0;
		while (s[len] != c && s[len])
			len++;
		if (len)
			str[i++] = ft_substr(s, 0, len);
		while (s[len] == c && s[len])
			len++;
		s += len;
	}
	str[i] = NULL;
	str = ft_free_all(str, i);
	return (str);
}
