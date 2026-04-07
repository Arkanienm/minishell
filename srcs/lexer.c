/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:36 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 12:05:44 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *str, t_token *head)
{
	g_status = 2;
	printf("%s\n", str);
	if (head)
		ft_free_struct(head);
	head = NULL;
}

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

int	set_len_word(char *str, int i, char **word)
{
	int	len;

	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
				+ 1] == '<'))
		len = 2;
	else
		len = 1;
	(*word) = ft_substr(str, i, len);
	return (len);
}

char	*extract_word(int i, char *str)
{
	int		len;
	char	*word;
	int		q_state;

	q_state = 0;
	if (!check_meta_char(str[i], q_state))
		len = set_len_word(str, i, &word);
	else
	{
		len = i;
		while (check_meta_char(str[len], q_state))
		{
			q_state = update_quotes(q_state, len, str);
			len++;
		}
		word = ft_substr(str, i, len - i);
	}
	if (q_state != 0)
	{
		free(word);
		return (NULL);
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
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		word = extract_word(i, str);
		if (word == NULL)
		{
			ft_error("syntax error : quote is not closed", head);
			return (NULL);
		}
		new_node = lexer(word);
		ft_lstadd_back(&head, new_node);
		i += ft_strlen(word);
	}
	i += 2;
	return (head);
}
