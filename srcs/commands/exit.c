#include "minishell.h"

static int is_number(char *str)
{
    int i;

    i = 0;
    if(str[0] == '-' || str[0] == '+')
        i++;
    while(str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

void exit(char **args)
{
    long long int result;
    int error;

    if(!args || !args[1])
        exit(0);
    result = ft_atol(args[1], &error);
    if(error || is_number(args[1]) == 0)
    {
        write(2, "minishell: exit: needs numeric arguments\n", 42);
        exit(2);
    }
    if(count_tab_tab(args) > 2)
    {
        write(2, "minishell: exit: too many arguments\n", 37);
        return ;
    }
    exit((unsigned char)result);
}