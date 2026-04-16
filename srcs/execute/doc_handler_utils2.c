/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_handler_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:41 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/16 15:08:16 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	env_loop_heredoc(t_envp_data **env, char *key, char *line)
{
	while ((*env) && (!(*env)->keyword || ft_strcmp((*env)->keyword, key) != 0))
		(*env) = (*env)->next;
	if (!ft_strcmp(line, "\"$\""))
	{
		line = ft_strdup("$");
		return (0);
	}
	return (1);
}

char	*final_string_heredoc(int len, char *s2, char *line, char *key)
{
	char	*s1;
	char	*s3;

	s1 = ft_substr(line, len, ft_strlen(line));
	s3 = ft_strjoin(s2, s1);
	free(line);
	free(s1);
	free(s2);
	free(key);
	return (s3);
}

void	replace_word_heredoc(char **line, int *i, t_envp_data *env)
{
	int		len;
	char	*s1;
	char	*s2;
	char	*key;

	len = (*i) + 1;
	while (ft_isalnum((*line)[len]) || (*line)[len] == '_')
		len++;
	key = ft_substr((*line), (*i) + 1, (len - ((*i) + 1)));
	if (!env_loop_heredoc(&env, key, (*line)))
		return ;
	s1 = ft_substr((*line), 0, (*i));
	if (env)
	{
		s2 = ft_strjoin(s1, env->value);
		(*i) += ft_strlen(env->value) - 1;
	}
	else
	{
		s2 = ft_strjoin(s1, "");
		(*i)--;
	}
	free(s1);
	(*line) = final_string_heredoc(len, s2, (*line), key);
}

void	replace_status_heredoc(char **line, int *i)
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
	s1 = ft_substr((*line), 0, (*i));
	s2 = ft_strjoin(s1, status);
	free(s1);
	s1 = ft_substr((*line), len, ft_strlen(*line) - len);
	s3 = ft_strjoin(s2, s1);
	free(*line);
	*line = s3;
	free(s1);
	free(s2);
	(*i) += ft_strlen(status) - 1;
	free(status);
}

char	*expander_heredoc(char *line, t_envp_data *env)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line && line[i + 1] == '?')
				replace_status_heredoc(&line, &i);
			else if (line && line[i + 1] != ' ' && line[i + 1] != '\0' && line
				[i + 1] != 39)
				replace_word_heredoc(&line, &i, env);
		}
		i++;
	}
	return (line);
}
