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
LIB_DIR   := lib
LIBFT_DIR := $(LIB_DIR)/libft
MLX_DIR   := $(LIB_DIR)/mlx_linux
INC_DIRS  := include $(LIBFT_DIR) $(MLX_DIR)
SRC_DIRS  := tuples canvas matrices rays shapes lights materials helpers world
SRC_DIRS  += camera
SRC_DIRS  := $(addprefix src/, $(SRC_DIRS))
SRC_DIRS  += src

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

LIBFT   := $(LIBFT_DIR)/libft.a
MLX     := $(MLX_DIR)/libmlx_Linux.a

HEADERS := tuples.h canvas.h matrices.h rays.h shapes.h lights.h materials.h
HEADERS += world.h helpers.h camera.h mlx.h

SOURCES := main.c models.c basic_math.c vector_math.c colors.c canvas.c
SOURCES += mx_attributes.c mx_operations.c mx_rotations.c mx_transformations.c
SOURCES += mx_utils.c rays.c intersections.c spheres.c
SOURCES += lights.c materials.c guards.c world.c view_transform.c camera.c
SOURCES += render.c controls.c shapes.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

################################################################################
##                                 COMPILATION                                ##
################################################################################

CFLAGS  := -O2 -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -L $(MLX_DIR)
LDLIBS  := -lft -lmlx -lXext -lX11 -lm

all: $(NAME)

r: $(NAME)
	@make $(TEST) -C tests --no-print-directory

test: $(NAME)
	@make -C tests --no-print-directory

$(NAME): $(OBJS) | $(LIBFT) $(MLX)
	@$(LOG) "Linking objects to $@"
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(LOG) "Compiling $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating objects directory"
	@mkdir $@

$(LIBFT):
	@make bonus -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@make -C $(MLX_DIR) --no-print-directory

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
	@$(LOG) "Removing libft"
	@make fclean -C $(LIBFT_DIR) --no-print-directory --silent
	@$(LOG) "Removing mlx"
	@make clean -C $(MLX_DIR) --no-print-directory --silent

re: clean all

.PHONY: all clean fclean re
