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

extern int				g_status;

typedef struct s_envp_data
{
	char				*keyword;
	char				*value;
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

t_envp_data				*get_envp_path(char **envp);
void					ft_free_struct(t_token *lst);
int						update_quotes(int q_state, int len, char *str);
int						check_meta_char(char c, int q_state);
t_token					*tokenizer(char *str);
void					expander(t_token *head, t_envp_data *env);
void					remove_quotes(t_token *head);
void					free_cmd_struct(t_cmd *lst);
void					ft_free_struct(t_token *lst);
void					parser(t_token *head, t_cmd **cmd_lst);
void					ft_echo(int fd, char *content);
int						cd(char *path, t_envp_data *envp);
void					print_env(t_envp_data *envp);
void					export(char *str, t_envp_data **envp);
int						count_tab_tab(char **envp);
void					free_tab_tab(char **envp);
void					copy_tab_tab(char **src, char **dest);
int						len_value(char *str);
int						len_before_equal(char *str);
char					*get_keyword(char *str);
int						unset(char *key, t_envp_data **envp);
long long int			ft_atol_exit(const char *str, int *error);
void					pwd(int fd);
long long int	ft_exit(t_cmd *cmd, t_envp_data *envp);
void					setup_signals(void);
t_cmd					*ft_lstnew_cmd(void *content);
void					ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void					ft_lstadd_back_redir(t_redir **lst, t_redir *new);
void					ft_lstadd_back(t_token **lst, t_token *new);
t_token					*ft_lstnew(void *content);
int						ft_lstsize_data(t_envp_data *data);
int						path_home(char **path, char **old_p, char **tmp_p, t_envp_data **envp);
int						path_not_found(char **home_p, char **old_p, t_envp_data **envp, char *path);
int						path_error(char **path, char **old_path);
int						verif_pwd(t_envp_data **envp);
char					*find_line_envp(char *to_find, t_envp_data *envp);
void					exp_tmp(int *verif, int *size, t_envp_data **data, t_envp_data **tmp);
void					printing_sorted_env(t_envp_data **data, int size);
void					free_envp_data(t_envp_data *envp);
void					write_redir_error(t_token *current);
int						minishell_loop(t_envp_data *envp);
void					ft_free_data(t_envp_data *data);
void					free_all(t_envp_data *envp);
int						set_envp_path(t_envp_data **data, char **envp, t_envp_data **new);
int						verif_cmd_redir(t_token *current);
int						q_state_set(int i, t_token *current, int q_state);
int						verif_line(char *line);
int						check_alnum(char *str);
int						atoll_loop(int **error, int sign, int digit);

# include "pipex.h"
#endif