NAME = minitalk

SERVER = server

CLIENT = client

CC = gcc

CFLAGS = -g3 -Wall -Werror -Wextra

SRCS_CLIENT = client.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

SRCS_SERVER = server.c vector.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)

SRCS_COMMON = ft_utils.c

OBJS_COMMON = $(SRCS_COMMON:.c=.o)

.PHONY: all clean fclean re

$(NAME): $(SERVER) $(CLIENT)

all: $(NAME)

$(SERVER): $(OBJS_COMMON) $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_SERVER) -o $(SERVER)

$(CLIENT) : $(OBJS_COMMON) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_CLIENT) -o $(CLIENT)

clean:
	-rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_COMMON)

fclean: clean
	-rm -f $(CLIENT) $(SERVER)

re: fclean all
