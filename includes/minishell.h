/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:52:15 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/04 11:38:48 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_status;

typedef struct s_envp_data {
	char *keyword;
	char *value;
	struct s_envp_data *next;
} t_envp_data;

typedef enum e_token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
} t_token_type;

typedef struct s_token
{
    char			*content;
    t_token_type	type;
    struct s_token	*next;
}   t_token;

typedef struct s_redir
{
	int				type;
	char 			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char 			**cmd;
	struct s_cmd	*next;
	t_redir	*redir;
}	t_cmd;

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

t_envp_data	*get_envp_path(char **envp);
void		ft_error(char *str, t_token *head);
void		ft_free_struct(t_token *lst);
int			update_quotes(int q_state, int len, char *str);
int			check_meta_char(char c, int q_state);
t_token		*tokenizer(char *str);
void		expander(t_token *head, t_envp_data *env);
int			ft_strcmp(char *s1, char *s2);
void		remove_quotes(t_token *head);
void		free_cmd_struct(t_cmd *lst);
void		ft_free_struct(t_token *lst);
void		parser(t_token *head, t_cmd **cmd_lst);
void		ft_free_redir(t_redir *lst);



#endif