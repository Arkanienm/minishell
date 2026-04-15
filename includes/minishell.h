/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:45:53 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/15 16:01:16 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# define P_RESET "\001\033[0m\002"
# define P_RED "\001\033[31m\002"
# define P_GREEN "\001\033[32m\002"
# define P_CYAN "\001\033[36m\002"

extern int	g_status;

typedef struct s_envp_data
{
	char				*keyword;
	char				*value;
	int					equal;
	struct s_envp_data	*next;
}						t_envp_data;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}						t_token_type;

typedef struct s_token
{
	char				*content;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char				**cmd;
	struct s_cmd		*next;
	t_redir				*redir;
}						t_cmd;

typedef struct s_atol
{
	int					i;
	long long int		nb;
	int					sign;
	long long			max_div;
	int					digit;
}						t_atol;

typedef struct s_exec
{
	int					null_fd;
	int					ret;
	int					fd[2];
	char				buf[4096];
	t_cmd				**cmds;
}						t_exec;

t_envp_data				*get_envp_path(char **envp);
void					ft_free_struct(t_token *lst);
char					*final_string(int len, char *s2, t_token *current,
							char *key);
void					replace_status(t_token *current, int *i);
int						update_quotes(int q_state, int len, char *str);
int						check_meta_char(char c, int q_state);
t_token					*tokenizer(char *str);
void					expander(t_token *head, t_envp_data *env);
void					remove_quotes(t_token *head);
void					free_cmd_struct(t_cmd *lst);
void					ft_free_struct(t_token *lst);
void					parser(t_token *head, t_cmd **cmd_lst);
void					ft_echo(int fd, char *content);
int						cd(char *path, t_envp_data **envp);
void					print_env(t_envp_data *envp);
void					export(char *str, t_envp_data **envp);
int						count_tab_tab(char **envp);
void					free_tab_tab(char **envp);
void					copy_tab_tab(char **src, char **dest);
int						len_value(char *str);
int						len_bef_equal(char *str);
char					*get_keyword(char *str);
int						unset(char *key, t_envp_data **envp);
long long int			ft_atol_exit(const char *str, int *error);
void					print_pwd(int fd, t_envp_data *envp);
long long int			ft_exit(t_cmd *cmd, t_envp_data *envp);
void					setup_signals(void);
t_cmd					*ft_lstnew_cmd(void *content);
void					ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void					ft_lstadd_back_redir(t_redir **lst, t_redir *new);
void					ft_lstadd_back(t_token **lst, t_token *new);
t_token					*ft_lstnew(void *content);
int						ft_lstsize_data(t_envp_data *data);
int						path_home(char **path, char **old_p, char **tmp_p,
							t_envp_data **envp);
int						path_not_found(char **home_p, char **old_p,
							t_envp_data **envp, char *path);
int						path_error(char **path, char **old_path);
int						verif_pwd(t_envp_data **envp);
char					*find_line_envp(char *to_find, t_envp_data *envp);
void					exp_tmp(int *verif, int *size, t_envp_data **data,
							t_envp_data **tmp);
void					printing_sorted_env(t_envp_data **data, int size);
void					free_envp_data(t_envp_data *envp);
void					write_redir_error(t_token *current);
int						minishell_loop(t_envp_data **envp);
void					ft_free_data(t_envp_data *data);
void					free_all(t_envp_data *envp);
int						set_envp_path(t_envp_data **data, char **envp,
							t_envp_data **new);
int						verif_cmd_redir(t_token *current);
int						q_state_set(int i, t_token *current, int q_state);
int						verif_line(char *line);
int						check_alnum(char *str);
int						atoll_loop(int **error, int sign, int digit);
int						check_sign(const char *nptr, int *i, int *sign);
int						check_nb(int **error, long long int nb,
							long long int max_div);
int						check_space(const char *nptr, t_atol *st_atol);
int						ft_isspace(int c);
int						check_str_equal(char *str);
int						cd_dash(t_envp_data **envp);
int						check_str_equal(char *str);
int						exec_exit(int fd[2], t_cmd *cmd, t_envp_data *envp);
int						exec_env(t_envp_data **envp);
int						exec_echo(t_cmd *cmd);
int						exec_echo_with_n(t_cmd *cmd);
int						exec_pwd(t_envp_data **envp);
int						exec_export(t_cmd *cmd, t_envp_data **envp);
int						exec_unset(t_cmd *cmd, t_envp_data **envp);
int						exec_cd(t_cmd *cmd, t_envp_data **envp);
int						exec_cd_dash(t_cmd *cmd, t_envp_data **envp);
int						is_n_flag(char *str);
int						print_and_return(void);
int						check_path_is_ok(char *path, char *home_path,
							char *old_path, t_envp_data **envp);
void					update_oldpwd(int *num_envp, t_envp_data **envp,
							t_envp_data *current, char *old_path);
int						find_num_envp(char *to_find, t_envp_data *envp);
void					update_tab_data(t_envp_data **envp, t_envp_data ***data,
							int *i);
int						count_envp_values(t_envp_data *envp);
;
void					free_miniloop(t_token **token, t_cmd **cmd,
							char **line);
void					free_miniloop_exec(t_token **token, t_cmd **cmd);

#endif