/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:20 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/17 18:44:40 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(char *str, t_token *token)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		token->type = PIPE;
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		token->type = APPEND;
	else
		token->type = WORD;
	token->content = str;
}

int	tokenizer(char **argv, t_token *token)
{
	int	i;
	char	**args;
	
	i = 0;
	while (argv[i])
	{
		lexer(argv[i], token);
		token = token->next;
		i++;
	}
}

int	parsing(int argc, char **argv)
{
	
}