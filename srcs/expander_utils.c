/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:15 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/15 15:58:53 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_status(t_token *current, int *i)
{
	char	*status;
	char	*s1;
	char	*s2;
	char	*s3;
	int		len;

	len = (*i) + 2;
	status = ft_itoa(g_status);
	if (!status)
		return ;
	s1 = ft_substr(current->content, 0, (*i));
	s2 = ft_strjoin(s1, status);
	free(s1);
	s1 = ft_substr(current->content, len, ft_strlen(current->content) - len);
	s3 = ft_strjoin(s2, s1);
	free (current->content);
	current->content = s3;
	free (s1);
	free (s2);
	(*i) += ft_strlen(status) - 1;
	free (status);
}

char	*final_string(int len, char *s2, t_token *current, char *key)
{
	char	*s1;
	char	*s3;

	s1 = ft_substr(current->content, len, ft_strlen(current->content));
	s3 = ft_strjoin(s2, s1);
	free(current->content);
	free(s1);
	free(s2);
	free(key);
	return (s3);
}
