TESTS := tuples matrices transformations

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

OBJ_DIR   := ../obj
SRC_DIR   := ../src
LIBFT_DIR := ../libft
INC_DIRS  := ../include $(LIBFT_DIR)

# Insert each new directory here
SRC_DIRS := tuples matrices
SRC_DIRS := $(addprefix $(SRC_DIR)/, $(SRC_DIRS))
SRC_DIRS += $(SRC_DIR)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

SOURCES := models.c basic_math.c vector_math.c
SOURCES += mx_attributes.c mx_operations.c mx_rotations.c mx_transformations.c mx_utils.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -lcriterion -lm

define run
 	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ && ./$@ --verbose
endef

################################################################################
##                                 TESTS                                      ##
################################################################################

all: $(TESTS) clean

.PHONY: tuples
tuples: $(OBJS) test_tuples.c
	@$(call run, "$^")

.PHONY: matrices
matrices: $(OBJS) test_matrices.c
	@$(call run, "$^")

.PHONY: transformations
transformations: $(OBJS) test_transformations.c
	@$(call run, "$^")

# Makefile rules to clean stdin/stdout/stderr test's files
clean:
	@$(RM) -r $(TESTS)
	@$(LOG) "Removing objects"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
