##
## EPITECH PROJECT, 2021
## LIB SOCKET
## File description:
## LIB SOCKET MAKEFILE
##

DSRC	= ./src/

SRC_FILES = socket_client_hostname_connect.c	\
			socket_client_ip_connect.c			\
			socket_close.c						\
			debug_socket.c						\
			fd_getline.c						\
			fd_getline_delim.c					\
			fd_read.c							\
			socket_send.c						\
			socket_server_connect.c				\
			socket_server_create.c				\
			fd_select.c							\
			utility/find_newline.c				\
			utility/is_empty.c					\

SRC 	=	$(addprefix $(DSRC), $(SRC_FILES))

OBJ		=	$(SRC:.c=.o)

NAME 	= libmysocket.a

CFLAGS	= -Wall -Wextra -W -Werror -I./include

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ) && \
     	$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREN) "$(NAME)\n"$(DEFAULT) || \
  		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

debug: CFLAGS += -g
debug: re

re: fclean all

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $< && \
		$(ECHO) $(GREEN_C) "cc $(CFLAGS) -c "$<$(COLOR_THEME)" -o "$@ $(DEFAULT) || \
		$(ECHO) "\n"$(MAGEN_C) $(UNDLN_T)$(BOLD_T)"cc $(CFLAGS) -c "$<" -o "$@$(DEFAULT)"\n"

.PHONY: clean fclean re debug

ECHO    =       /bin/echo -e
DEFAULT =       "\e[0m"
BOLD_T  =       "\e[1m"
DIM_T   =       "\e[2m"
UNDLN_T =       "\e[4m"
BLACK_C =       "\e[30m"
RED_C   =       "\e[31m"
GREEN_C =       "\e[32m"
YELLO_C =       "\e[33m"
BLUE_C  =       "\e[34m"
MAGEN_C =       "\e[35m"
CYAN_C  =       "\e[36m"
WHITE_C =       "\e[97m"
DEFAULT_C       =       "\e[39m"
LINE_RETURN     =       $(ECHO) ""
COLOR_THEME     =       $(CYAN_C)
DEBUG_THEME     =       $(CYAN_C)
TESTS_THEME     =       $(RED_C)