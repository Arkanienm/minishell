/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:43 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/03 15:38:50 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_status = 0;

void	ft_free_data(t_envp_data *data)
{
	t_envp_data	*nnext;

	while (data)
	{
		nnext = data->next;
		if (data->keyword)
			free(data->keyword);
		if (data->value)
			free(data->value);
		free(data);
		data = nnext;
	}
}

int	print_and_return(void)
{
	ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	g_status = 2;
	return (-1);
}

int	verif_line(char *line)
{
	if (!line)
	{
		(printf(P_RED "exit\n" P_RESET));
		return (0);
	}
	return (1);
}

void	free_all(t_envp_data *envp)
{
	if(envp)
		free_envp_data(envp);
	envp = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_envp_data	*env;
	int			status;

	if (argc != 1)
		return (0);
	(void)argv;
	setup_signals();
	env = get_envp_path(envp);
	g_status = 0;
	status = minishell_loop(&env);
	free_all(env);
	return (status);
}
