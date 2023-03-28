NAME		= libft.a

SRCS		= ft_isalpha.c ft_toupper.c ft_isdigit.c ft_tolower.c ft_isalnum.c   \
				ft_isascii.c ft_isprint.c ft_strlen.c ft_strchr.c ft_strrchr.c   \
				ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_memset.c  \
				ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c      \
				ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c       \
				ft_strtrim.c ft_split.c ft_itoa.c ft_itoa_base.c ft_strmapi.c    \
				ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c     \
				ft_putnbr_fd.c ft_isspace.c ft_abs.c ft_atol.c

BONUS		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c            \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c       \
				ft_lstmap.c

OBJDIR		= obj
OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJDIR)/, $(BONUS:.c=.o))

CFLAGS		= -Wall -Wextra -Werror -O3
RM			= rm -f

CYAN	= \33[1;36m
NC		= \033[0m

LOG	= printf "[$(CYAN)INFO$(NC)] "

all:		$(NAME)

$(NAME):	$(OBJDIR) $(OBJS) gnl printf

bonus:		$(OBJDIR) $(OBJS) $(OBJS_BONUS) gnl printf

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	src/%.c
	$(CC) $(CFLAGS) -I. -c $< -o $@
	ar -rc $(NAME) $@

gnl:
	@$(LOG)
	@echo "Compiling $@"
	@make -C gnl --no-print-directory

printf:
	@$(LOG)
	@echo "Compiling $@"
	@make -C printf --no-print-directory

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) -r $(OBJDIR)
	@make clean -C gnl --no-print-directory
	@make clean -C printf --no-print-directory

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus gnl printf
