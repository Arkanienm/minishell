/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:45:13 by mg                #+#    #+#             */
/*   Updated: 2026/02/28 15:00:21 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_envp_size(char **envp)
{
    int i;

    i = 0;
    while(envp[i])
        i++;
    return i;
}

char *get_keyword(char *str)
{
    int i;
    char *dest;
    
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    dest = malloc(sizeof(char) * (i + 1));
    if(!dest)
        return NULL;
    ft_strlcpy(dest, str, i + 1);
    return dest;
}

int len_before_equal(char *str)
{
    int i;

    if (ft_strchr(str, '=') == 0)
        return 0;
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    return i;
}

int len_value(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if(str[0] == '\0')
        return 0;
    while (str[j] && str[j] != '=')
        j++;
    while(str[i + j])
        i++;
    return i - 1;
}

t_envp_data *get_envp_path(char **envp)
{
    int i;
    t_envp_data *data;
    t_envp_data *new;
    t_envp_data *initial;

    if(!envp || !envp[0])
        return NULL;
    i = 0;
    data = malloc(sizeof(t_envp_data));
    if(!data)
        return NULL;
    initial = data;
    while(envp[i])
    {
        data->keyword = get_keyword(envp[i]);
        data->value = ft_substr(envp[i], len_before_equal(envp[i]) + 1, len_value(envp[i]));
        if(envp[i + 1] == NULL)
            data->next = NULL;
        else
        {
            new = malloc(sizeof(t_envp_data));
            if(!new)
                return NULL;
            data->next = new;
            data = new;
        }
        i++;
    }
    return initial;
}


// int main(int argc, char **argv, char **envp)
// {
//    (void)argc;
//    (void)argv;
//    t_envp_data *data;

//    data = get_envp_path(envp);
//    while(data)
//    {
// 		printf("%s=%s\n", data->keyword, data->value);
//         data = data->next;
//    }
//    return 0;
// }