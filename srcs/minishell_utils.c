#include "../includes/minishell.h"

int	verif_cmd_redir(t_token *current)
{
	if (!current->next)
		return (1);
	if (current->next->next)
		return (1);
	if (!current->next->next)
	{
		if (current->type == WORD && current->next->type != WORD)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'",
				2);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
	}
	return (1);
}

void	ft_free_struct(t_token *lst)
{
	t_token	*nnext;

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

void	ft_free_redir(t_redir *lst)
{
	t_redir	*nnext;

	nnext = lst;
	if (!lst)
		return ;
	while (lst)
	{
		nnext = lst->next;
		if (lst->file)
			free(lst->file);
		free(lst);
		lst = nnext;
	}
}

void	free_cmd_struct(t_cmd *lst)
{
	t_cmd	*nnext;
	int		i;

	i = 0;
	nnext = lst;
	if (!lst)
		return ;
	while (lst)
	{
		nnext = lst->next;
		if (lst->cmd)
		{
			i = 0;
			while (lst->cmd[i])
			{
				free(lst->cmd[i]);
				i++;
			}
			free(lst->cmd);
		}
		if (lst->redir)
			ft_free_redir(lst->redir);
		free(lst);
		lst = nnext;
	}
}

void	write_redir_error(t_token *current)
{
	if (current->next->type == PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	else if (current->next->type == REDIR_IN)
		ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
	else if (current->next->type == REDIR_OUT)
		ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
	else if (current->next->type == APPEND)
		ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
	else if (current->next->type == HEREDOC)
		ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
}
