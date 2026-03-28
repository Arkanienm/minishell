#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

static int is_n_flag(char *str)
{
	int i;

	i = 0;
	if(!str || str[0] != '-' || str[1] != 'n')
		return 0;
	i = 1;
	while(str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int execute_builtin(t_cmd *cmd, t_envp_data **envp, int *in, int *out)
{
	int i;
	int exit_code;

	i = 0;
	if (!ft_strcmp(cmd->cmd[0], "cd") && cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-") == 0)
	{
		if(cmd->cmd[1] && cmd->cmd[2])
		{
			ft_putstr_fd("cd : too many arguments\n", 2);
			g_status = 1;
			return 1;
		}
		else
		{
			if(cd_dash(envp) == -1)
				g_status = 1;
			else
				g_status = 0;
		}
	}
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
	{
		if(cmd->cmd[1] && cmd->cmd[2])
		{
			ft_putstr_fd("cd : too many arguments\n", 2);
			g_status = 1;
			return 1;
		}
		else
		{
			if(cd(cmd->cmd[1], *envp) == -1)
				g_status = 1;
			else
				g_status = 0;
		}
	}
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
	{
		if(cmd->cmd[1])
			unset(cmd->cmd[1], envp);
		g_status = 0;
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
		g_status = 0;
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "echo") && is_n_flag(cmd->cmd[1]))
	{
		i = 1;
		while(cmd->cmd[i] && is_n_flag(cmd->cmd[i]))
			i++;
		while(cmd->cmd[i])
		{
			ft_echo(1, cmd->cmd[i]);
			if(cmd->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		g_status = 0;
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
		g_status = 0;
		write(1, "\n", 1);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "env"))
	{
		print_env(*envp);
		g_status = 0;
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
	{
		restore_fds(in, out);
		exit_code = ft_exit(cmd, *envp);
		if(exit_code == -1)
		{
			save_fds(in, out);
			return 1;
		}
		else if (exit_code == -2)
		{
			g_status = 2;
			save_fds(in, out);
			return (2);
		}
		g_status = exit_code;
		return 2;
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
