NAME = minirt

CC = cc

CFLAGS = # -Wall -Werror -Wextra
LIBXFLAGS = -lmlx_Linux -lXext -lX11
# LIBXFLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS_DIR = srcs
INCLUDES_DIR = include

SOURCES = $(wildcard $(SRCS_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

HEADERS = $(wildcard $(INCLUDES_DIR)/*.h)

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a
	$(CC) $(OBJECTS) $(LIBXFLAGS) -o $(NAME) libft/libft.a

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES_DIR) -Imlx

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

bonus:
	$(MAKE) all BONUS_FLAG=yes

debug: CFLAGS += -g -DDEBUG=1
debug: re

libft.a: libft/libft.a
	cp libft/libft.a .

libft/libft.a:
	$(MAKE) -C libft

.PHONY: all clean fclean re bonus debug
