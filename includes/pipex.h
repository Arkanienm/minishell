#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "minishell.h"

typedef struct s_data
{
	int		last_status;
	int		should_exit;
	int		last_was_builtin;
	int		heredoc_fd;
	int		end[2];
	int		infile;
	int		outfile;
	int		previous_read;
	pid_t	pid;
	t_token	*token;
	t_cmd	*cmd;
	t_envp_data *env;
	char **envp_tab;
	char	*line;
}			t_data;

void		init_data(t_data *data);
void		perror_exit(char *error_message, int code_exit);
char		*return_path(char *cmd, char **env);
void		free_tab(char **tab_to_free);
int		exec_loop(t_data *data, char **envp, t_cmd *cmds,
				t_envp_data **envp_struct);
char		*ft_strjoin_pipex(char *s1, char *s2);
void		error_exit(char *error, int exit_code);
void		cmd_loop(t_data *data, t_cmd *current);
int			loop_redir(t_data *data, t_redir *redir);
void		redirect(t_data *data, t_cmd *cmds);
int			pipex(t_envp_data *envp, t_cmd *cmds);
char		**struct_to_envp(t_envp_data *envp);
int	handle_heredoc(t_data *data, t_redir *redir);
int			apply_redir(t_data *data, t_redir *redir);
int			execute_builtin(t_cmd *cmd, t_envp_data **envp, int *in, int *out);
int			detect_builtin(t_cmd *cmd);
int pre_Handler_heredoc(t_data *data, t_cmd *cmds);
int			manage_redir_in(t_data **data, t_redir **redir);
int			manage_redir_out(t_data **data, t_redir **redir);
int			manage_redir_append(t_data **data, t_redir **redir);
void		restore_fds(int *in, int *out);
void		save_fds(int *in, int *out);
void		set_sign_ignore(void);
void		set_sign_def(void);
void		setup_signals(void);
void handle_sigint_heredoc(int sig);


#endif