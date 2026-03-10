NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I. 

SRCS_DIR    = srcs/
OBJ_DIR     = .obj/
LIBFT_DIR   = ./includes/Libft/
COMMANDS_DIR = ./srcs/commands/

SRCS        = $(SRCS_DIR)minishell.c $(SRCS_DIR)get_envp_path.c $(SRCS_DIR)expander.c \
              $(SRCS_DIR)lexer.c $(SRCS_DIR)parsing.c $(SRCS_DIR)quotes_utils.c $(COMMANDS_DIR)cd.c \
			  $(COMMANDS_DIR)commands_utils.c $(COMMANDS_DIR)echo.c $(COMMANDS_DIR)env.c $(COMMANDS_DIR)export.c \
			  $(COMMANDS_DIR)pwd.c $(COMMANDS_DIR)unset.c $(SRCS_DIR)minishell_utils.c 
OBJS        = $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT       = $(LIBFT_DIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

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