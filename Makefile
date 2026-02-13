NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I.

SRCS        = srcs/minishell.c srcs/get_envp_path.c srcs/parsing.c


OBJ_DIR     = .obj/

OBJS        = $(SRCS:%.c=$(OBJ_DIR)%.o)

LIBFT       	= ./includes/Libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./includes/Libft/
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o: %.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C ./includes/Libft

fclean: clean
	rm -f $(NAME)
	make clean -C ./includes/Libft

re: fclean all

.PHONY: all clean fclean re
