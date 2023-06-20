export LIBRARY_PATH = $(HOME)/.brew/lib
export C_INCLUDE_PATH = $(HOME)/.brew/Cellar/criterion/2.4.1_2/include

NAME    	:= minishell
UNIT_TEST	:= test.out

ifdef DEBUG
CFLAGS += -g
endif

ifdef FSAN
CFLAGS += -fsanitize=address,undefined
endif

#=================== DIRECTORIES ===================#
BUILD_DIR	:=	build
OBJ_DIR     :=  ./obj
SRC_DIR     :=  ./src
INC_DIR     :=  ./include ./libft/include
LIBFT_DIR	:=	./libft
TEST_DIR	:=	./tests

#=================== LIBRARIES ===================#

CFLAGS  	+= 	-Wextra -Wall -Werror
CFLAGS  	+=	 $(addprefix -I, $(shell brew --prefix readline)/include)

LDFLAGS  	= 	-L$(shell brew --prefix readline)/lib -lreadline -L./libft -lft

ifdef TEST
CRIT_FLAGS	= 	-I$(shell brew --prefix criterion)/include -lcriterion
endif
# CRIT_FLAGS	= 	$(addprefix -I, $(shell brew --prefix criterion)/include)
CRIT_FLAGS	= -I$(shell brew --prefix criterion)2.4.1_2/include # -I/Users/vbrouwer/.brew/Cellar/criterion/2.4.1_2/include

#=================== GENERAL VARIABLES ===================#

INCLUDE     			:= $(addprefix -I,$(INC_DIR))

MAIN					:=	src/main.c

SRC						:=  shell/minishell.c \
						  	lexer/tokenizer.c \
							lexer/token_list_functions.c \
							parser/parser.c \
							parser/syntax.c \
							parser/syntax_jt_funcs.c \
							parser/commands.c \
							parser/command_utils.c \
							parser/clean_functions.c \
							parser/heredoc.c \
							parser/expansion.c \
							executor/executor.c \
							executor/pipeline.c \
							executor/execution_utils.c \
							executor/execute_built_in.c \
							executor/execute_non_built_in.c \
							executor/handle_redir.c \
							lexer/token_analysis.c \
							builtins/echo.c \
							builtins/cd.c \
							builtin/pwd.c \
							builtins/env.c \
							# builtin/builtin_utils.c \

# unit = SRC

# SRC += SRC \
# 		main.c

ODIR					:=	$(sort $(dir $(SRC:%=$(OBJ_DIR)/%)))
SRC     				:=	$(SRC:%=$(SRC_DIR)/%)

MAIN_OBJ				:=	$(MAIN:src/%.c=$(OBJ_DIR)/%.o)
OBJS					:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT					:= $(LIBFT_DIR)/libft.a

#=================== TESTS ===================#
#	Unit	test	Directories
UNIT_DIR				:=	unit_tests
UNIT_BUILD_DIR			:=	$(UNIT_DIR)/$(BUILD_DIR)
UNIT_SRC_DIR			:=	$(UNIT_DIR)/$(SRC_DIR)
UNIT_INCLUDE_DIR		:=	$(UNIT_DIR)/$(INCLUDE_DIR)

UNIT_SRCS				:=	$(wildcard $(UNIT_DIR)/$(SRC_DIR)/*.c)
UNIT_OBJS				:=	$(patsubst $(UNIT_DIR)/$(SRC_DIR)/%.c, $(UNIT_DIR)/$(BUILD_DIR)/$(notdir %.o), $(UNIT_SRCS))

UNIT_HEADERS			:=	$(wildcard $(UNIT_DIR)/$(INCLUDE_DIR)/*.h)
UNIT_INCLUDE_FLAGS		:=	-I$(UNIT_DIR)
#UNIT_INCLUDE_FLAGS		:=	$(addprefix -I, $(sort $(dir $(UNIT_HEADERS))))

#===============================================#
#=================== RECIPES ===================#
#===============================================#

# echo:
# 	@echo

all: $(ODIR) $(NAME)

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

$(ODIR):
	mkdir -p $@

$(MAIN_OBJ): $(MAIN)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(NAME)

$(LIBFT):
	git submodule update --init --recursive
	@$(MAKE) -C $(LIBFT_DIR)

#=================== TEST RECIPES ===================#
tester: all $(UNIT_TEST)

test:
	@$(MAKE) TEST=1 tester
	@./$(UNIT_TEST)

testclean:
	@rm -rf $(UNIT_TEST)

test_re: fclean tester

$(UNIT_TEST): $(UNIT_OBJS) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(UNIT_OBJS) $(OBJS) $(LDFLAGS) $(INCLUDE) $(CRIT_FLAGS) $(LIBS) -o $(UNIT_TEST)

$(UNIT_OBJS): $(UNIT_BUILD_DIR)/%.o: $(UNIT_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) -o $@

# $(TEST)/bin:
# 	mkdir $@

# $(TEST)/bin/%: $(TEST)/%.c
# 	$(CC) $(CFLAGS) $(LDFLAGS) $< $(OBJS) -o $@ -lcriterion

# test: all $(TEST)/bin $(TESTBINS)
# 	for test in $(TESTBINS) ; do ./$$test ; done

.PHONY: all, clean, fclean, re, fsan, resan, debug, rebug, test, test_re
.DEFAULT_GOAL := all
