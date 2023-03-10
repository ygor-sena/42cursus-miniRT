NAME		= ../libft.a

OBJ			= obj

SRCS		= $(addprefix src/, ft_printf.c parser.c printer.c)
PRS_SRC		= $(addprefix src/parse/, flags.c parse_utils.c)
PRT_SRC		= $(addprefix src/print/, types.c out_char.c                \
				out_string.c out_pointer.c out_signed.c out_unsigned.c  \
				out_percent.c print_utils.c)

SRC_OBJ		= $(subst src, obj, $(SRCS:.c=.o))
PRS_OBJ		= $(subst src/parse, obj, $(PRS_SRC:.c=.o))
PRT_OBJ		= $(subst src/print, obj, $(PRT_SRC:.c=.o))

CFLAGS		= -Wall -Wextra -Werror -O3
RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJ) $(SRC_OBJ) $(PRS_OBJ) $(PRT_OBJ)

define compile
	$(CC) $(CFLAGS) -c $< -I.. -o $@
	ar -rc $(NAME) $@
endef

$(OBJ):
	@mkdir -p $(OBJ)

$(OBJ)/%.o:	src/%.c
	$(compile)

$(OBJ)/%.o:	src/parse/%.c
	$(compile)

$(OBJ)/%.o:	src/print/%.c
	$(compile)

clean:
	$(RM) -r $(SRC_OBJ) $(PRS_OBJ) $(PRT_OBJ)
	$(RM) -r $(OBJ)

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re
