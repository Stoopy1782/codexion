CC = cc -Wall -Wextra -Werror

.PHONY: all clean fclean re

all:
	$(CC) main.c split.c
