#include "../../includes/minishell.h"

static long long int	ft_atoll(const char *nptr, int *error)
{
	t_atol	st_atol;

	st_atol.i = 0;
	st_atol.sign = 0;
	st_atol.nb = 0;
	st_atol.max_div = 922337203685477580ULL;
	if (!check_space(nptr, &st_atol))
		return (0);
	while (nptr[st_atol.i] >= '0' && nptr[st_atol.i] <= '9')
	{
		st_atol.digit = nptr[st_atol.i] - 48;
		if (!check_nb(&error, st_atol.nb, st_atol.max_div))
			return (0);
		if (st_atol.nb == st_atol.max_div)
		{
			if (atoll_loop(&error, st_atol.sign, st_atol.digit) == 0)
				return (0);
		}
		st_atol.nb = st_atol.nb * 10 + nptr[st_atol.i++] - 48;
	}
	if (st_atol.sign == 1)
		return (-(long long)st_atol.nb);
	return ((long long)st_atol.nb);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '\0')
			return (0);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	check_cmd_signal(t_cmd *cmd)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putstr_fd("exit\n", 2);
	if (!cmd->cmd[1])
		return (0);
	return (1);
}

long long int	ft_exit(t_cmd *cmd, t_envp_data *envp)
{
	long long	code;
	int			error;

	error = 0;
	(void)envp;
	if (!check_cmd_signal(cmd))
		return (g_status);
	if (!is_numeric(cmd->cmd[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (-2);
	}
	if (count_tab_tab(cmd->cmd) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_status = 1;
		return (-1);
	}
	code = ft_atoll(cmd->cmd[1], &error);
	if (error)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (-2);
	}
	return (((code % 256) + 256) % 256);
}
