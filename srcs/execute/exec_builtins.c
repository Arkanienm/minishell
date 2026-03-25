#include "../../includes/minishell.h"

int execute_builtin(t_cmd *cmd, t_envp_data **envp)
{
	int i;

	if (!ft_strcmp(cmd->cmd[0], "cd"))
	{
		if(cmd->next)
		{
			ft_putstr_fd("too many arguments", 2);
			g_status = 1;
		}
		cd(cmd->cmd[1], *envp);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
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
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
	{
		ft_exit(cmd);
		return 1;
	}
	return 0;
}

#include "../../includes/minishell.h"

int detect_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		return 1;
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return 1;
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return 1;
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return 1;
	else if (!ft_strcmp(cmd->cmd[0], "echo") && cmd->cmd[1] && !ft_strcmp(cmd->cmd[1], "-n"))
		return 1;
	else if (!ft_strcmp(cmd->cmd[0], "echo"))
		return 1;
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return 1;
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return 1;
	return 0;
}
