# Makefile for your project

# Compiler and flags
CC := cc
CFLAGS := -g -pthread -Wall -Werror -Wextra

## -fsanitize=thread

SRCS_LOC = philo

# Source files
SRCS = $(SRCS_LOC)/main.c $(SRCS_LOC)/libft.c $(SRCS_LOC)/safe.c \
$(SRCS_LOC)/get_set_safe.c $(SRCS_LOC)/time_utils.c $(SRCS_LOC)/dinner.c \
$(SRCS_LOC)/init.c $(SRCS_LOC)/write.c $(SRCS_LOC)/utils.c \

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
NAME = philosopher

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c philosopher.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
