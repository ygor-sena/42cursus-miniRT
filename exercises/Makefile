TESTS := projectile

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

SRC_DIR   := ../src
OBJ_DIR   := ../obj
LIB_DIR   := ../lib
LIBFT_DIR := $(LIB_DIR)/libft
MLX_DIR   := $(LIB_DIR)/mlx_linux
INC_DIRS  := ../include $(LIBFT_DIR) $(MLX_DIR)

# Insert each new directory here
SRC_DIRS := tuples canvas matrices
SRC_DIRS += $(addprefix $(SRC_DIR)/, $(SRC_DIRS))
SRC_DIRS += $(SRC_DIR)

CHAPTERS := ch02
SRC_DIRS += $(CHAPTERS)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

LIBFT   := $(LIBFT_DIR)/libft.a
MLX     := $(MLX_DIR)/libmlx_Linux.a

SOURCES := models.c basic_math.c vector_math.c colors.c canvas.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -L $(MLX_DIR)
LDLIBS  := -lft -lmlx -lXext -lX11 -lm

define run
 	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@ && ./$@ --verbose
endef

################################################################################
##                                 EXERCISES                                  ##
################################################################################

all: $(TESTS) clean

$(OBJS):
	@make -C ..

.PHONY: projectile
projectile: $(OBJS) projectile.c
	@$(call run, "$^")

clean:
	@$(RM) -r $(TESTS)
	@$(LOG) "Removing objects"

fclean: clean

re: fclean all

.PHONY: all clean fclean re