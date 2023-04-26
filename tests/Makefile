TESTS := tuples colors matrices transformations rays spheres intersections
TESTS += lights materials world view_transform camera

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

SRC_DIR   := ../src
OBJ_DIR   := ../obj
LIBFT_DIR := ../lib/libft
MLX_DIR   := ../lib/mlx_linux
INC_DIRS  := ../include $(LIBFT_DIR) $(MLX_DIR)

# Insert each new directory here
SRC_DIRS := tuples canvas matrices rays shapes tests lights materials helpers
SRC_DIRS += camera
SRC_DIRS += $(addprefix $(SRC_DIR)/, $(SRC_DIRS))
SRC_DIRS += $(SRC_DIR)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

SOURCES := models.c basic_math.c vector_math.c colors.c
SOURCES += mx_attributes.c mx_operations.c mx_rotations.c mx_transformations.c
SOURCES += mx_utils.c rays.c intersections.c spheres.c
SOURCES += lights.c materials.c guards.c world.c view_transform.c camera.c
SOURCES += canvas.c render.c controls.c shadows.c

UTILS := utils.c
OBJS  := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))
OBJS  += $(UTILS:.c=.o)

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -L $(MLX_DIR)
LDLIBS  := -lft -lmlx -lXext -lX11 -lm -lcriterion 

define run
 	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@ && ./$@ --verbose
endef

################################################################################
##                                 TESTS                                      ##
################################################################################

all: $(TESTS) clean

.PHONY: tuples
tuples: $(OBJS) test_tuples.c
	@$(call run, "$^")

.PHONY: colors
colors: $(OBJS) test_colors.c
	@$(call run, "$^")

.PHONY: matrices
matrices: $(OBJS) test_matrices.c
	@$(call run, "$^")

.PHONY: transformations
transformations: $(OBJS) test_transformations.c
	@$(call run, "$^")

.PHONY: rays
rays: $(OBJS) test_rays.c
	@$(call run, "$^")

.PHONY: spheres
spheres: $(OBJS) test_spheres.c
	@$(call run, "$^")

.PHONY: intersections
intersections: $(OBJS) test_intersections.c
	@$(call run, "$^")

.PHONY: lights
lights: $(OBJS) test_lights.c
	@$(call run, "$^")

.PHONY: materials
materials: $(OBJS) test_materials.c
	@$(call run, "$^")

.PHONY: world
world: $(OBJS) test_world.c
	@$(call run, "$^")

.PHONY: view_transform
view_transform: $(OBJS) test_view_transform.c
	@$(call run, "$^")

.PHONY: camera
camera: $(OBJS) test_camera.c
	@$(call run, "$^")

# Makefile rules to clean stdin/stdout/stderr test's files
clean:
	@$(RM) -r $(TESTS)
	@$(LOG) "Removing objects"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
