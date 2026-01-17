LIB_NAME = libperlin.a

CC = gcc
CFLAGS = -Wall -Wextra -O2

SRCS = map_gen.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB_NAME) test.exe