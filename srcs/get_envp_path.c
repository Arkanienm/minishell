/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:45:13 by mg                #+#    #+#             */
/*   Updated: 2026/02/12 13:48:00 by mg               ###   ########.fr       */
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
    dest[i + 1] = '\0';
    while(i-- >= 0)
        dest[i] = str[i];
    return dest;
}

int len_before_equal(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    return i + 1;
}

int len_value(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[j] && str[j] != '=')
        j++;
    while(str[i + j])
        i++;
    return i;
}

t_envp_data *get_envp_path(char **envp)
{
    int i;
    t_envp_data *data;
    t_envp_data *new;
    t_envp_data *initial;

    i = 0;
    data = malloc(sizeof(t_envp_data));
    initial = data;
    while(envp[i])
    {
        data->keyword = get_keyword(envp[i]);
        data->value = ft_substr(envp[i], len_before_equal(envp[i]), len_value(envp[i]));
        if(envp[i + 1] == NULL)
            data->next = NULL;
        else
        {
            new = malloc(sizeof(t_envp_data));
            data->next = new;
            new = data;
        }
        i++;
    }
    return initial;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_envp_data *data;

    data = get_envp_path(envp);
    while(data)
    {
        printf("%s\n", data->keyword);
        data = data->next;
    }
    return 0;
}