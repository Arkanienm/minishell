#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include "minishell.h"

typedef struct s_data
{
	int		end[2];
	int		infile;
	int		outfile;
	char	**cmd_cmd;
	int		previous_read;
	int		i;
	int		is_heredoc;
	int		nb_cmd;
	pid_t	pid;
}			t_data;

void		init_data(t_data *data, int argc, char **argv);
void		perror_exit(char *error_message, int code_exit);
char		*return_path(char *cmd, char **env);
void		free_tab(char **tab);
void		handle_heredoc(t_data *data, char **argv);
void		get_files(t_data *data, int argc, char **argv);
void		exec_loop(t_data *data, char **argv, char **envp);
char		*ft_strjoin_pipex(char *s1, char *s2);
void		error_exit(char *error, int exit_code);
void		cmd_loop(t_data *data);

#endif