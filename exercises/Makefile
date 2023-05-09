###############################################################################
### Just replace the filename and the current chapter
EXERCISE := add_planes
CHAP_DIR := ch9

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

SRC_DIR   := ../src
OBJ_DIR   := ../obj
LIB_DIR   := ../lib
LIBFT_DIR := $(LIB_DIR)/libft
MLX_DIR   := $(LIB_DIR)/mlx_linux
INC_DIRS  := ../include $(LIBFT_DIR) $(MLX_DIR)

SRC_DIRS := $(shell find $(SRC) -type d)
SRC_DIRS += $(CHAP_DIR)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

LIBFT   := $(LIBFT_DIR)/libft.a
MLX     := $(MLX_DIR)/libmlx_Linux.a

SOURCES := $(shell find $(SRC_DIR) -name '*.c' -exec basename {} \;)
SOURCES := $(filter-out main.c, $(SOURCES))
OBJS    := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -L $(MLX_DIR)
LDLIBS  := -lft -lmlx -lXext -lX11 -lm

all: $(EXERCISE)

$(OBJS):
	@make -C .. --no-print-directory

$(EXERCISE): $(OBJS) $(EXERCISE).c
	@$(CC) -O3 $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@ && ./$@

clean:
	@$(RM) -r $(EXERCISE)
	@$(LOG) "Removing objects"

fclean: clean

re: fclean all

.PHONY: all clean fclean re $(EXERCISE)
