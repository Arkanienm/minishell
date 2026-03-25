#include "minishell.h"

int execute_builtin(t_cmd *cmd, t_envp_data **envp)
{
	int i;

	if (!ft_strcmp(cmd->cmd[0], "cd"))
	{
		cd(cmd->cmd[1], *envp);
		return 1;
	}
	if (!ft_strcmp(cmd->cmd[0], "unset"))
	{
		if (!cmd->cmd[1])
			ft_putstr_fd("unset: not enough arguments\n", 2);
		else
			unset(cmd->cmd[1], envp);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "export"))
	{
		export(cmd->cmd[1], envp);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
	{
		if (cmd->cmd[1])
			ft_putstr_fd("pwd: too many arguments\n", 2);
		else
		pwd(1);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "echo") && cmd->cmd[1] && !ft_strcmp(cmd->cmd[1], "-n"))
	{
		i = 2;
		while(cmd->cmd[i])
		{
			ft_echo(1, cmd->cmd[i]);
			if(cmd->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "echo"))
	{
		i = 1;
		while(cmd->cmd[i])
		{
			ft_echo(1, cmd->cmd[i]);
			if(cmd->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "env"))
	{
		print_env(*envp);
		return 1;
	}
	return 0;
}
