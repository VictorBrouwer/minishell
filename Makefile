export LIBRARY_PATH = $(HOME)/.brew/lib
export C_INCLUDE_PATH = $(HOME)/.brew/Cellar/criterion/2.4.1_2/include
# export LIBRARY_PATH = $(HOME)/homebrew/lib
# export C_INCLUDE_PATH = $(HOME)/homebrew/Cellar/criterion/2.4.1_2/include

NAME		:=	minishell
UNIT_TEST	:=	test.out

#=================== DIRECTORIES ===================#
BUILD_DIR	:=	build
OBJ_DIR		:=	./obj
SRC_DIR		:=	./src
INC_DIR 	:=	./include ./libft/include
LIBFT_DIR	:=	./libft
TEST_DIR	:=	./tests

#=================== LIBRARIES ===================#

CFLAGS			:=	-Wextra -Wall -Werror
CFLAGS			+=	$(addprefix -I, $(shell brew --prefix readline)/include)

ifdef DEBUG
	CFLAGS += -g
endif

ifdef FSAN
	CFLAGS += -fsanitize=address,undefined
endif

LDFLAGS			=	-L$(shell brew --prefix readline)/lib -lreadline -L./libft -lft

ifdef TEST
CRIT_FLAGS		=	-I$(shell brew --prefix criterion)/include -lcriterion
endif

#=================== GENERAL VARIABLES ===================#

INCLUDE					:= $(addprefix -I,$(INC_DIR))

MAIN					:=	src/main.c

SRC						:=  shell/minishell.c \
							lexer/tokenizer.c \
							lexer/token_list_functions.c \
							lexer/tokenizer_utils.c \
							lexer/find_tokens.c \
							parser/parser.c \
							parser/syntax.c \
							parser/syntax_jt_funcs.c \
							parser/commands.c \
							parser/command_utils.c \
							parser/clean_functions.c \
							parser/heredoc.c \
							parser/expansion.c \
							parser/expansion_utils.c \
							parser/command_fill_utils.c \
							executor/executor.c \
							executor/execution_utils.c \
							executor/execute_built_in.c \
							executor/execute_non_built_in.c \
							executor/handle_redir.c \
							executor/simple_command.c \
							executor/pipeline.c \
							builtins/builtin_utils.c \
							builtins/cd.c \
							builtins/echo.c \
							builtins/env.c \
							builtins/exit.c \
							builtins/export.c \
							builtins/pwd.c \
							builtins/unset.c \
							env/env_list_funcs.c \
							env/env_utils.c \
							env/env_utils2.c \
							utils/minishell_utils.c \
							utils/error_handling.c \
							signals/signal_handler.c \

ODIR					:=	$(sort $(dir $(SRC:%=$(OBJ_DIR)/%)))
SRC     				:=	$(SRC:%=$(SRC_DIR)/%)

MAIN_OBJ				:=	$(MAIN:src/%.c=$(OBJ_DIR)/%.o)
OBJS					:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT					:=	$(LIBFT_DIR)/libft.a

#===============================================#
#=================== RECIPES ===================#
#===============================================#

all: $(LIBFT) $(ODIR) $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(UNIT_TEST)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

debug:
	$(MAKE) DEBUG=1

rebug: fclean debug

fsan:
	$(MAKE) DEBUG=1 FSAN=1

resan: fclean fsan

$(LIBFT):
	git submodule update --init --recursive --remote
	@$(MAKE) -C $(LIBFT_DIR)

$(ODIR):
	mkdir -p $@

$(MAIN_OBJ): $(MAIN)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(NAME)

#mem:
#    $(HOME)/memdetect/memdetect.sh . $(GCC_FLAGS) $(1)

.PHONY: all, clean, fclean, re, fsan, resan, debug, rebug
.DEFAULT_GOAL := all
