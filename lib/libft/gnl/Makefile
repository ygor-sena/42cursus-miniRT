NAME		= ../libft.a

SRC			= get_next_line.c get_next_line_utils.c
GNL_OBJ	= $(SRC:.c=.o)

CFLAGS		= -Wall -Wextra -Werror -O3
OPEN_MAX = $(shell getconf OPEN_MAX)

all:		$(NAME)

$(NAME): $(GNL_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -D OPEN_MAX=$(OPEN_MAX) -c $< -o $@
	ar -rc $(NAME) $@

clean:
	$(RM) -r $(GNL_OBJ)

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re
