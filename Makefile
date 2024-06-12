NAME = miniRT

CC = cc

CFLAGS =  -Wall -Werror -Wextra
CFLAGS += -g -fsanitize=address
LIBXFLAGS = -lmlx_Linux -lXext -lX11  -lm
# LIBXFLAGS = -lmlx -lXext -lX11  -lm
# LIBXFLAGS = -lmlx -framework OpenGL -framework AppKit

INCLUDES_DIR = include
SRCDIR = ./srcs ./srcs/read


SRCS   = $(foreach SRCDIR,$(SRCDIR),$(wildcard $(SRCDIR)/*.c))
OBJECTS = $(SRCS:.c=.o)

HEADERS = $(wildcard $(INCLUDES_DIR)/*.h)

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a	
	@echo $(GREEN)
	@echo "╭━╮╭━╮╱╱╱╱╱╱╱╱╭━━━╮╭━━━━╮"
	@echo "┃┃╰╯┃┃╱╱╱╱╱╱╱╱┃╭━╮┃┃╭╮╭╮┃"
	@echo "┃╭╮╭╮┃╭╮╭━╮╱╭╮┃╰━╯┃╰╯┃┃╰╯"
	@echo "┃┃┃┃┃┃┣┫┃╭╮╮┣┫┃╭╮╭╯╱╱┃┃"
	@echo "┃┃┃┃┃┃┃┃┃┃┃┃┃┃┃┃┃╰╮╱╱┃┃"
	@echo "╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰━╯╱╱╰╯"
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBXFLAGS) -o $(NAME) libft/libft.a


%.o:%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES_DIR) -Imlx


clean:
	@rm -f $(OBJECTS)
	@$(MAKE) -C libft clean
	@echo $(BRIGHT_MAGENTA)
	@echo ╭━╮╭╮╱╭━╮╭━━╮╭━┳╮╭━┳╮╭━━╮╭━┳╮╭━━╮
	@echo ┃╭╯┃┃╱┃┳╯┃╭╮┃┃┃┃┃┃┃┃┃╰┃┃╯┃┃┃┃┃╭━┫
	@echo ┃╰╮┃╰╮┃┻╮┃┣┫┃┃┃┃┃┃┃┃┃╭┃┃╮┃┃┃┃┃╰╮┃╭╮╭╮╭╮
	@echo ╰━╯╰━╯╰━╯╰╯╰╯╰┻━╯╰┻━╯╰━━╯╰┻━╯╰━━╯╰╯╰╯╰╯

fclean:
	@rm -f $(OBJECTS)
	@$(MAKE) -C libft clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo $(RED)╭━━━╮$(BRIGHT_MAGENTA)
	@echo $(RED)┃╭━━╯$(BRIGHT_MAGENTA)
	@echo $(RED)┃╰━━╮$(BRIGHT_MAGENTA) ╭━╮╭╮╱╭━╮╭━━╮╭━┳╮╭━┳╮╭━━╮╭━┳╮╭━━╮
	@echo $(RED)┃╭━━╯$(BRIGHT_MAGENTA) ┃╭╯┃┃╱┃┳╯┃╭╮┃┃┃┃┃┃┃┃┃╰┃┃╯┃┃┃┃┃╭━┫
	@echo $(RED)┃┃ $(BRIGHT_MAGENTA) ╱╱┃╰╮┃╰╮┃┻╮┃┣┫┃┃┃┃┃┃┃┃┃╭┃┃╮┃┃┃┃┃╰╮┃╭╮╭╮╭╮
	@echo $(RED)╰╯ $(BRIGHT_MAGENTA)╱╱ ╰━╯╰━╯╰━╯╰╯╰╯╰┻━╯╰┻━╯╰━━╯╰┻━╯╰━━╯╰╯╰╯╰╯$(RESET)


re: fclean all

bonus:
	$(MAKE) all BONUS_FLAG=yes

debug: CFLAGS += -g -DDEBUG=1
debug: re

libft.a: libft/libft.a
	cp libft/libft.a .

libft/libft.a:
	@$(MAKE) -C libft

echo:
	echo $(SRCS)

.PHONY: all clean fclean re bonus debug

1:
	./$(NAME) map/1.rt

2:
	./$(NAME) map/2.rt

3:
	./$(NAME) map/3.rt

4:
	./$(NAME) map/4.rt

5:
	./$(NAME) map/5.rt



















# color
RESET = "\033[0m"
# 標準色
BLACK = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"
# 明るい色
BRIGHT_BLACK = "\033[90m"
BRIGHT_RED = "\033[91m"
BRIGHT_GREEN = "\033[92m"
BRIGHT_YELLOW = "\033[93m"
BRIGHT_BLUE = "\033[94m"
BRIGHT_MAGENTA = "\033[95m"
BRIGHT_CYAN = "\033[96m"
BRIGHT_WHITE = "\033[97m"
# 背景色
BG_RED = "\033[41m"
BG_GREEN = "\033[42m"
BG_BLUE = "\033[44m"
BG_WHITE = "\033[47m"
# テキスト属性
BOLD = "\033[1m"
UNDERLINE = "\033[4m"
REVERSE = "\033[7m"
coffee:
	@echo ""
	@echo "                   ("
	@echo "                         )     ("
	@echo "               ___...(-------)-....___"
	@echo '           .-""       )    (          ""-.'
	@echo "      .-''''|-._             )         _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
