/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:20 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/20 16:47:16 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*lexer(char *str)
{
	t_token	*new_node;

	new_node = ft_lstnew(str);
	if (ft_strncmp(str, "|", 2) == 0)
		new_node->type = PIPE;
	else if (ft_strncmp(str, "<", 2) == 0)
		new_node->type = REDIR_IN;
	else if (ft_strncmp(str, ">", 2) == 0)
		new_node->type = REDIR_OUT;
	else if (ft_strncmp(str, "<<", 3) == 0)
		new_node->type = HEREDOC;
	else if (ft_strncmp(str, ">>", 3) == 0)
		new_node->type = APPEND;
	else
		new_node->type = WORD;
	return (new_node);
}

int	check_meta_char(char c)
{
	if (c && c != ' ' && c != '>' && c != '<' && c != '|')
		return (1);
	return (0);
}

char	*extract_word(int i, char *str)
{
	int		len;
	char	*word;

	len = 0;
	if (!check_meta_char(str[i]))
	{
		if ((str[i] == '>' && str[i + 1] == '>' ) || (str[i] == '<'
				&& str[i + 1] == '<'))
			len = 2;
		else
			len = 1;
		word = ft_substr(str, i, len);
	}
	else
	{
		len = i;
		while (check_meta_char(str[len]))
			len ++;
		word = ft_substr(str, i, len - i);
	}
	return (word);
}

t_token	*tokenizer(char *str)
{
	int		i;
	t_token	*head;
	t_token	*new_node;
	char	*word;

	head = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		word = extract_word(i, str);
		new_node = lexer(word);
		ft_lstadd_back(&head, new_node);
		i += ft_strlen(word);
	}
	return (head);
}
