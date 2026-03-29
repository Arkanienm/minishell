#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	exec_echo_with_n(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i] && is_n_flag(cmd->cmd[i]))
		i++;
	while (cmd->cmd[i])
	{
		ft_echo(1, cmd->cmd[i]);
		if (cmd->cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	g_status = 0;
	return (1);
}

int	exec_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		ft_echo(1, cmd->cmd[i]);
		if (cmd->cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	g_status = 0;
	write(1, "\n", 1);
	return (1);
}

int	exec_env(t_envp_data **envp)
{
	print_env(*envp);
	g_status = 0;
	return (1);
}

int	exec_exit(int fd[2], t_cmd *cmd, t_envp_data *envp)
{
	int	exit_code;

	restore_fds(&fd[0], &fd[1]);
	exit_code = ft_exit(cmd, envp);
	if (exit_code == -1)
	{
		save_fds(&fd[0], &fd[1]);
		return (1);
	}
	else if (exit_code == -2)
	{
		g_status = 2;
		save_fds(&fd[0], &fd[1]);
		return (2);
	}
	g_status = exit_code;
	return (2);
}
