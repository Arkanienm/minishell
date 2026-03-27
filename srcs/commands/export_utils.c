#include "../../includes/minishell.h"

void	exp_tmp(int *verif, int *size, t_envp_data **data, t_envp_data **tmp)
{
	int	i;

	while ((*verif) == 1)
	{
		(*verif) = 0;
		i = 0;
		while (i < (*size) - 1)
		{
			if (ft_strcmp(data[i]->keyword, data[i + 1]->keyword) > 0)
			{
				(*tmp) = data[i];
				data[i] = data[i + 1];
				data[i + 1] = (*tmp);
				(*verif) = 1;
			}
			i++;
		}
	}
}

void	printing_sorted_env(t_envp_data **data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		write(1, "declare -x ", 11);
		ft_putstr_fd(data[i]->keyword, 1);
		if (data[i]->value)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_putstr_fd(data[i]->value, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

int	check_alnum(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) == 1)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
