CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_PATH) -Iinclude

LIBFT_PATH = lib/libft
LIBFT = $(LIBFT_PATH)/libft.a

LOGO = lib/minishell_logo.txt
NAME = minishell
HEADER = minishell.h

SRC = src/00_core/main.c\
		src/00_core/ms_error_0.c\
		src/00_core/ms_error_1.c\
		src/00_core/ms_exit.c\
		src/00_core/ms_garbage.c\
		src/00_core/ms_init.c\
		src/00_core/ms_signals.c\
		src/00_core/ms_helper_functions.c\
		src/00_core/ms_utilities.c\
		src/00_core/ms_handle_errors.c\
		src/01_input/in_handling.c\
		src/01_input/in_input.c\
		src/01_input/in_operators.c\
		src/01_input/in_parentheses.c\
		src/01_input/in_quotes.c\
		src/01_input/prompt_dir.c\
		src/01_input/prompt_formatting.c\
		src/01_input/prompt_user_host.c\
		src/01_input/in_helpers.c\
		src/02_tokenizing/tok_cmdsub.c\
		src/02_tokenizing/tok_expand.c\
		src/02_tokenizing/tok_operators.c\
		src/02_tokenizing/tok_quotes.c\
		src/02_tokenizing/tok_redirect.c\
		src/02_tokenizing/tok_segments.c\
		src/02_tokenizing/tok_tokenize.c\
		src/02_tokenizing/tok_word.c\
		src/02_tokenizing/tok_assign.c\
		src/03_parsing/heredoc_helpers.c\
		src/03_parsing/heredoc.c\
		src/03_parsing/parse_merge.c\
		src/03_parsing/parse_ops_paren.c\
		src/03_parsing/parse_parsing.c\
		src/03_parsing/parse_redirections.c\
		src/04_exec/start_exec_ast.c\
		src/04_exec/exec_external.c\
		src/04_exec/exec_utils.c\
		src/04_exec/exec_cd_0.c\
		src/04_exec/exec_cd_1.c\
		src/04_exec/exec_echo.c\
		src/04_exec/exec_env.c\
		src/04_exec/exec_export_0.c\
		src/04_exec/exec_export_1.c\
		src/04_exec/exec_export_print_0.c\
		src/04_exec/exec_export_print_1.c\
		src/04_exec/exec_free.c\
		src/04_exec/exec_path.c\
		src/04_exec/exec_pipe.c\
		src/04_exec/exec_pwd.c\
		src/04_exec/exec_unset.c\
		src/04_exec/exec_redirect_0.c\
		src/04_exec/exec_redirect_1.c\
		src/04_exec/exec_redirect_2.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@cat $(LOGO)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft -lreadline

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -rf $(NAME)

asan: fclean
asan: CFLAGS += -fsanitize=address -g
asan: all

gdb: fclean
gdb: CFLAGS += -g -O0
gdb: all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --track-fds=yes  --quiet --suppressions=readline_suppress.supp ./minishell

valchild:
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --track-fds=yes  --trace-children=yes --quiet --suppressions=readline_suppress.supp ./minishell

re: fclean all

.PHONY: all clean fclean re compile asan
