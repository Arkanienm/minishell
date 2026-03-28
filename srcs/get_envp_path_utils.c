#include "../includes/minishell.h"

int	get_envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	*get_keyword(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, str, i + 1);
	return (dest);
}

int	len_before_equal(char *str)
{
	int	i;

	if (ft_strchr(str, '=') == 0)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	len_value(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] == '\0')
		return (0);
	while (str[j] && str[j] != '=')
		j++;
	while (str[i + j])
		i++;
	return (i - 1);
}

int	set_envp_path(t_envp_data **data, char **envp, t_envp_data **new)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		(*data)->keyword = get_keyword(envp[i]);
		(*data)->value = ft_substr(envp[i], len_before_equal(envp[i]) + 1,
				len_value(envp[i]));
		(*data)->equal = 1;
		if (envp[i + 1] == NULL)
			(*data)->next = NULL;
		else
		{
			(*new) = malloc(sizeof(t_envp_data));
			if (!(*new))
				return (0);
			(*data)->next = (*new);
			(*data) = (*new);
		}
		i++;
	}
	return (1);
}
