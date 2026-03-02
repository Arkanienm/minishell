/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:49:39 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/02 14:53:57 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status = 0;

void print_token(t_token *head)
{
	t_token *current;

	current = head;
	while (current)
	{
		printf("Token [%s] | Type %u\n", current->content, current->type);
		current = current->next;
	}
}

int	minishell_loop(t_envp_data *env)
{
	t_token		*token;
	char *line;
	
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			exit (0);
		if (line)
			add_history(line);
		token = tokenizer(line);
		if (token)
		{
			expander(token, env);
			remove_quotes(token);
			print_token(token);
		}
		ft_free_struct(token);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp_data *env;
	
	if (argc != 1)
		return (0);
	(void)argv;
	env = get_envp_path(envp);
	g_status = 0;
	minishell_loop(env);
}