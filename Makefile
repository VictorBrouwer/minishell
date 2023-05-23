NAME	:= minishell

OBJ_DIR		:=	./obj
SRC_DIR 	:=	./src
INC_DIR		:=	./include ./libft/include

CFLAGS  = -Wextra -Wall -Werror -I/Users/vbrouwer/.brew/opt/readline/include
LFLAGS  = -L/Users/vbrouwer/.brew/opt/readline/lib -lreadline -L./libft -lft

ifdef DEBUG
CFLAGS +=-g
endif

ifdef FSAN
CFLAGS += -fsanitize=address,undefined
endif

INCLUDE		:= $(addprefix -I,$(INC_DIR))

SRC		:=	main.c \
			lexer/tokenizer.c \
			lexer/token_list_functions.c \

SRC		:= $(SRC:%=$(SRC_DIR)/%)

OBJS	:=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(notdir %.o), $(SRC))

LIBFT		:= ./libft
LIBS		:= $(LIBFT)/libft.a

#===============================================#
#=================== RECIPES ===================#
#===============================================#

all: submodule $(NAME)

submodule:
	git submodule update --init --recursive

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

re: fclean all

debug:
	$(MAKE) DEBUG=1

rebug: fclean debug

fsan:
	$(MAKE) DEBUG=1 FSAN=1

resan: fclean fsan

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(OBJ_DIR)/$(notdir $@)

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(OBJS))) $(LFLAGS) -o $(NAME)

.PHONY: all, clean, fclean, re, fsan, resan, debug, rebug