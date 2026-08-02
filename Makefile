NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = \
	main.c \
	routine.c \
	setup.c \
	simulate.c \
	time.c \
	print.c \
	coder_command.c \
	monitor.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
