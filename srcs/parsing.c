/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:20 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/23 14:16:09 by amurtas          ###   ########.fr       */
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

int	check_meta_char(char c, int q_state)
{
	if (q_state == 0)
	{
		if (c && c != ' ' && c != '>' && c != '<' && c != '|')
			return (1);
	}
	else if (q_state == 2)
	{
		if (c != '\0')
			return (1);
	}
	else if (q_state == 1)
	{
		if (c != '\0')
			return (1);
	}
	return (0);
}

int	update_quotes(int q_state, int len, char *str)
{
	if (str[len] == 34 && q_state == 0)
		q_state = 2;
	else if (str[len] == 34 && q_state == 2)
		q_state = 0;
	else if (str[len] == 39 && q_state == 0)
		q_state = 1;
	else if (str[len] == 39 && q_state == 1)
		q_state = 0;
	return (q_state);
}

char	*extract_word(int i, char *str)
{
	int		len;
	char	*word;
	int		q_state;

	q_state = 0;
	if (!check_meta_char(str[i], q_state))
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
		while (check_meta_char(str[len], q_state))
		{
			q_state = update_quotes(q_state, len, str);
			len ++;
		}
		word = ft_substr(str, i, len - i);
	}
	if (q_state != 0)
	{
		free (word);
		return (NULL);
	}
	return (word);
}

void	ft_error(char *str)
{
	printf("%s\n", str);
}

void	ft_free_struct(t_token *lst)
{
	t_token *nnext;

	nnext = lst;
	if (!lst)
		return ;
	while (lst)
	{
		nnext = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = nnext;
	}
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
		if (word == NULL)
		{
			ft_error("syntax error : quote is not closed");
			ft_free_struct(head);
			return (NULL);
		}
		new_node = lexer(word);
		ft_lstadd_back(&head, new_node);
		i += ft_strlen(word);
	}
	return (head);
}

t_token	expander(t_token *head, char **envp)
{
	
}
