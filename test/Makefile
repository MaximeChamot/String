NAME		= test

SRCS		= main.c

OBJS		= $(SRCS:.c=.o)

CC		= gcc

RM		= rm -f

LXXFLAGS	= -L. -lstring

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
