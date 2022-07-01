NAME = minitalk

SERVER = server

CLIENT = client

CC = gcc

CFLAGS = -g3 -Wall -Werror -Wextra

SRCS_CLIENT = client.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

SRCS_SERVER = server.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)

.PHONY: all clean fclean re

$(NAME): $(SERVER) $(CLIENT)

all: $(NAME)

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER)

$(CLIENT) : $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT)

clean:
	-rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	-rm -f $(CLIENT) $(SERVER)

re: fclean all
