/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:52:15 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/04 21:20:44 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_envp_data {
    char *keyword;
    char *value;
	char ***envp;
    struct s_envp_data *next;
} t_envp_data;

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "Libft/libft.h"

int count_tab_tab(char **envp);
void free_tab_tab(char **envp);
void copy_tab_tab(char **src, char **dest);
int len_value(char *str);
int len_before_equal(char *str);
char *get_keyword(char *str);
int unset(char *key, t_envp_data **envp);
long long int	ft_atol_exit(const char *str, int *error);

#endif