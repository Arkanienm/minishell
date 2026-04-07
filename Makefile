NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I. 

SRCS_DIR     = srcs/
OBJ_DIR      = .obj/
LIBFT_DIR    = ./includes/Libft/
COMMANDS_DIR = ./srcs/commands/
EXC_DIR 	 = ./srcs/execute/

SRCS        = $(SRCS_DIR)minishell.c $(SRCS_DIR)free_all.c $(SRCS_DIR)get_envp_path.c $(SRCS_DIR)expander.c \
              $(SRCS_DIR)lexer.c $(SRCS_DIR)parsing.c $(SRCS_DIR)quotes_utils.c $(COMMANDS_DIR)cd.c \
			  $(COMMANDS_DIR)commands_utils.c $(COMMANDS_DIR)echo.c $(COMMANDS_DIR)env.c $(COMMANDS_DIR)export.c \
			  $(COMMANDS_DIR)pwd.c $(COMMANDS_DIR)cd_utils2.c $(COMMANDS_DIR)unset.c $(SRCS_DIR)minishell_utils.c $(SRCS_DIR)signals.c \
			  $(SRCS_DIR)ft_lstadd_back.c $(SRCS_DIR)ft_lstnew.c $(SRCS_DIR)ft_lstsize_data.c \
			  $(EXC_DIR)struct_to_envp.c $(EXC_DIR)pipex.c $(EXC_DIR)path.c \
			  $(EXC_DIR)init_data.c $(EXC_DIR)pipex_utils.c $(EXC_DIR)exec_cmd_builtins.c $(EXC_DIR)ft_strjoin_pipex.c $(EXC_DIR)doc-handler.c \
			  $(EXC_DIR)utils.c $(EXC_DIR)exec_cmd_builtins2.c $(EXC_DIR)exec_builtins.c $(COMMANDS_DIR)exit.c $(COMMANDS_DIR)cd_utils.c \
			  $(COMMANDS_DIR)export_utils.c $(EXC_DIR)doc_handler_utils.c $(EXC_DIR)doc_handler_utils2.c $(EXC_DIR)doc_handler_utils3.c $(SRCS_DIR)minishell_loop.c \
			  $(SRCS_DIR)get_envp_path_utils.c $(COMMANDS_DIR)atoll_utils.c $(COMMANDS_DIR)cd_dash.c $(EXC_DIR)execution.c \
			  $(EXC_DIR)execution_utils.c $(EXC_DIR)execution_utils2.c $(EXC_DIR)execution_utils3.c $(EXC_DIR)doc_handler_utils4.c 
OBJS        = $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT       = $(LIBFT_DIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -ltinfo -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re