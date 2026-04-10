/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:21 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 11:52:03 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (data[i]->equal == 1)
		{
			write(1, "=", 1);
			if (!data[i]->value)
				ft_putstr_fd("\"\"", 1);
		}
		if (data[i]->value)
		{
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

int	check_str_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	update_tab_data(t_envp_data **envp, t_envp_data ***data, int *i)
{
	if ((*envp)->keyword != NULL)
	{
		(*data)[*i] = *envp;
		*i += 1;
	}
	(*envp) = (*envp)->next;
}
