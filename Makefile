NAME    	:= minishell
UNIT_TEST	:=test.out

ifdef DEBUG
CFLAGS +=-g
endif

ifdef FSAN
CFLAGS += -fsanitize=address,undefined
endif

#=================== DIRECTORIES ===================#
BUILD_DIR	:=	./build
OBJ_DIR     :=  ./obj
SRC_DIR     :=  ./src
INC_DIR     :=  ./include ./libft/include
LIBFT       :=	./libft
TEST_DIR	:=	./tests

#=================== LIBRARIES ===================#

CFLAGS  = -Wextra -Wall -Werror #-I/Users/vbrouwer/.brew/opt/readline/include
CFLAGS  += $(addprefix -I, $(shell brew --prefix readline)/include)

LDFLAGS  = -L$(shell brew --prefix readline)/lib -lreadline -L./libft -lft

#=================== GENERAL VARIABLES ===================#

INCLUDE     := $(addprefix -I,$(INC_DIR))

SRC     :=  main.c \
			lexer/tokenizer.c \
			lexer/token_list_functions.c \
			lexer/token_analysis.c \

ODIR	:=	$(sort $(dir $(SRC:%=$(OBJ_DIR)/%)))
SRC     :=	$(SRC:%=$(SRC_DIR)/%)

# OBJS    :=  $(patsubst $(SRC_DIR)/%.c, $(ODIR)%.o, $(SRC))
OBJS	:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBS	:= $(LIBFT)/libft.a

#=================== TESTS ===================#
#	Unit	test	Directories
UNIT_DIR				:=unit_tests
UNIT_BUILD_DIR			:=$(UNIT_DIR)/$(BUILD_DIR)
UNIT_SRC_DIR			:=$(UNIT_DIR)/$(SRC_DIR)
UNIT_INCLUDE_DIR		:=$(UNIT_DIR)/$(INCLUDE_DIR)

UNIT_SRCS				:=$(wildcard $(UNIT_DIR)/$(SRC_DIR)/*.c)
UNIT_OBJS				:=$(patsubst $(UNIT_DIR)/$(SRC_DIR)/%.c, $(UNIT_DIR)/$(BUILD_DIR)/$(notdir %.o), $(UNIT_SRCS))

UNIT_HEADERS			:=$(wildcard $(UNIT_DIR)/$(INCLUDE_DIR)/*.h)
UNIT_INCLUDE_FLAGS		:=$(addprefix -I, $(sort $(dir $(UNIT_HEADERS))))

# TESTS	=	./tests/lexer_tests.c \
# TESTBINS=	$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

#===============================================#
#=================== RECIPES ===================#
#===============================================#

# echo:
# 	@echo $(ODIR)

all: $(ODIR) $(NAME)

# submodule:
# 	git submodule update --init --recursive

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(UNIT_TEST)
	@$(MAKE) fclean -C $(LIBFT)

re: fclean all

debug:
	$(MAKE) DEBUG=1

rebug: fclean debug

fsan:
	$(MAKE) DEBUG=1 FSAN=1

resan: fclean fsan

$(ODIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	git submodule update --init --recursive
	@$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

#=================== TEST RECIPES ===================#

test: $(UNIT_TEST) all

test_re: fclean test

$(UNIT_TEST): $(UNIT_OBJS) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(UNIT_OBJS) $(OBJS) $(LDFLAGS) $(UNIT_INCLUDE_FLAGS) $(INCLUDE) $(LIBS) -o $(UNIT_TEST)

$(UNIT_OBJS): $(UNIT_BUILD_DIR)/%.o: $(UNIT_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) -o $@

# $(TEST)/bin:
# 	mkdir $@

# $(TEST)/bin/%: $(TEST)/%.c
# 	$(CC) $(CFLAGS) $(LDFLAGS) $< $(OBJS) -o $@ -lcriterion

# test: all $(TEST)/bin $(TESTBINS)
# 	for test in $(TESTBINS) ; do ./$$test ; done

.PHONY: all, clean, fclean, re, fsan, resan, debug, rebug, test, test_re
.DEFAULT_GOAL := all
