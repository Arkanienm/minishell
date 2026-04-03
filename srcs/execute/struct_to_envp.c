/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:08 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/02 10:33:37 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "includes/minishell.h"

void	free_token_struct(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token->next;
		if (token->content)
			free(token->content);
		free(token);
		token = tmp;
	}
	return ;
}

static int	ft_envpsize(t_envp_data *envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp)
	{
		envp = envp->next;
		i++;
	}
	return (i);
}

static void	copy_value(char **envp_tab_i, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(*envp_tab_i, value);
	free(*envp_tab_i);
	*envp_tab_i = tmp;
}

char	**struct_to_envp(t_envp_data *envp)
{
	int		i;
	int		lines_envp;
	char	**envp_tab;
	char	*tmp;

	if (!envp)
		return (NULL);
	lines_envp = ft_envpsize(envp);
	i = 0;
	envp_tab = malloc(sizeof(char *) * (lines_envp + 1));
	if (!envp_tab)
		return (NULL);
	while (envp)
	{
		tmp = ft_strdup(envp->keyword);
		envp_tab[i] = ft_strjoin(tmp, "=");
		free(tmp);
		if (envp->value)
			copy_value(&envp_tab[i], envp->value);
		i++;
		envp = envp->next;
	}
	envp_tab[i] = NULL;
	return (envp_tab);
}

void	error_exit(char *error, int exit_code)
{
	ft_putstr_fd(error, 2);
	exit(exit_code);
}
