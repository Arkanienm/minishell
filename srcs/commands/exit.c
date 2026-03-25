#include "../../includes/minishell.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32 && c != '\0'))
		return (1);
	return (0);
}

static long long int	ft_atoll(const char *nptr)
{
	int				i;
	long long int	nb;
	int				sign;

	i = 0;
	sign = 0;
	nb = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = 1;
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	if (sign == 1)
		nb *= -1;
	return (nb);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '\0')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	long long	code;

	write(1, "exit\n", 5);
	if (!cmd->cmd[1])
		exit(g_status);
	if (!is_numeric(cmd->cmd[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	if (count_tab_tab(cmd->cmd) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_status = 1;
		return ;
	}
	code = ft_atoll(cmd->cmd[1]);
	exit(((code % 256) + 256) % 256);
}
