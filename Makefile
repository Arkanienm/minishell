NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I.

SRCS_DIR    = srcs/
OBJ_DIR     = .obj/
LIBFT_DIR   = ./includes/Libft/

SRCS        = $(SRCS_DIR)minishell.c $(SRCS_DIR)get_envp_path.c
OBJS        = $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT       = $(LIBFT_DIR)libft.a


all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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