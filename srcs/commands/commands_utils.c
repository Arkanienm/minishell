#include "minishell.h"

int count_tab_tab(char **envp)
{
    int i;

    i = 0;
	if(!envp || !envp[0])
		return 0;
    while(envp[i])
        i++;
    return i;
}

void free_tab_tab(char **envp)
{
    int i;

    i = 0;
    while(envp[i])
        free(envp[i]);
    free(envp);
}

void copy_tab_tab(char **src, char **dest)
{
    int i;

    i = 0;
	if(!src || !src[0])
		return NULL;
    while(src[i])
	{
        dest[i] = ft_strdup(src[i]);
		i++;
	}
    dest[i] = NULL;
    return ;
}

long long int	ft_atol_exit(const char *str, int *error)
{
	int				i;
	int				sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (sign == 1 && res > 9223372036854775807ULL)
			*error = 1;
		if (sign == -1 && res > 9223372036854775808ULL)
			*error = 1;
		i++;
	}
	return (res * sign);
}
