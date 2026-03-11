/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:52:15 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/11 17:37:51 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

extern int g_status;

typedef struct s_envp_data
{
	char *keyword;
	char *value;
	struct s_envp_data *next;
} t_envp_data;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
} t_token_type;

typedef struct s_token
{
	char *content;
	t_token_type type;
	struct s_token *next;
} t_token;

typedef struct s_redir
{
	int type;
	char *file;
	struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
	char **cmd;
	struct s_cmd *next;
	t_redir *redir;
} t_cmd;

#include "Libft/libft.h"
#include <curses.h>
#include <dirent.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

t_envp_data *get_envp_path(char **envp);
void ft_error(char *str, t_token *head);
void ft_free_struct(t_token *lst);
int update_quotes(int q_state, int len, char *str);
int check_meta_char(char c, int q_state);
t_token *tokenizer(char *str);
void expander(t_token *head, t_envp_data *env);
void remove_quotes(t_token *head);
void free_cmd_struct(t_cmd *lst);
void ft_free_struct(t_token *lst);
void parser(t_token *head, t_cmd **cmd_lst);
void ft_echo(int if_n, int fd, char *content);
int cd(char *path, t_envp_data *envp);
void print_env(t_envp_data *envp);
void export(char *str, t_envp_data **envp);
int count_tab_tab(char **envp);
void free_tab_tab(char **envp);
void copy_tab_tab(char **src, char **dest);
int len_value(char *str);
int len_before_equal(char *str);
char *get_keyword(char *str);
int unset(char *key, t_envp_data **envp);
long long int ft_atol_exit(const char *str, int *error);
void pwd(int fd);

#endif