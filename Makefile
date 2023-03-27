################################################################################
##                                MINIRT                                      ##
################################################################################

NAME  := miniRT

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR   := obj
LIBFT_DIR := libft
INC_DIRS  := include $(LIBFT_DIR)
SRC_DIRS  := tuples matrices
SRC_DIRS  := $(addprefix src/, $(SRC_DIRS))
SRC_DIRS  += src

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

LIBFT   := $(LIBFT_DIR)/libft.a

HEADERS := tuples.h matrices.h

SOURCES := main.c models.c basic_math.c vector_math.c
SOURCES += mx_attributes.c mx_operations.c mx_rotations.c mx_transformations.c mx_utils.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

################################################################################
##                                 COMPILATION                                ##
################################################################################

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -lm

all: $(NAME)

test: $(NAME)
	@make -C tests --no-print-directory

$(NAME):	$(OBJS) | $(LIBFT)
	@$(LOG) "Linking objects to $@"
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(LOG) "Compiling $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating objects directory"
	@mkdir $@

$(LIBFT):
	@make bonus -C $(LIBFT_DIR) --no-print-directory

checks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

clean:
	@$(RM) -r $(OBJS)
	@$(LOG) "Removing objects"
	@$(RM) -r $(OBJ_DIR)
	@$(LOG) "Removing objects directory"

fclean: clean
	@$(RM) -r $(NAME)
	@$(LOG) "Removing $(NAME)"
	@make fclean -C $(LIBFT_DIR) --no-print-directory --silent

re: clean all

.PHONY: all clean fclean re
