#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	exec_cd_dash(t_cmd *cmd, t_envp_data **envp)
{
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		g_status = 1;
		return (1);
	}
	else
	{
		if (cd_dash(envp) == -1)
			g_status = 1;
		else
			g_status = 0;
	}
	return (0);
}

int	exec_cd(t_cmd *cmd, t_envp_data **envp)
{
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		g_status = 1;
		return (1);
	}
	else
	{
		if (cd(cmd->cmd[1], *envp) == -1)
			g_status = 1;
		else
			g_status = 0;
	}
	return (0);
}

int	exec_unset(t_cmd *cmd, t_envp_data **envp)
{
	int	index;

	index = 0;
	if (cmd->cmd[1])
	{
		while (cmd->cmd[index])
			unset(cmd->cmd[index++], envp);
		index = 0;
	}
	g_status = 0;
	return (1);
}

int	exec_export(t_cmd *cmd, t_envp_data **envp)
{
	export(cmd->cmd[1], envp);
	return (1);
}

int	exec_pwd(t_envp_data **envp)
{
	print_pwd(1, *envp);
	g_status = 0;
	return (1);
}
