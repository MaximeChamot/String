NAME		= libstring.a

SRCS		= string.c

OBJS		= $(SRCS:.c=.o)

AR_RC		= ar rc

RANLIB		= ranlib

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR_RC) -o $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
