##
## EPITECH PROJECT, 2021
## Project_2021
## File description:
## Project makefile
##

DSRC	=	./src/

SRC_FILES_CLI	=	client/main.c		\

SRC_FILES_SRV	= 	server/main.c												\
					utility/signal_manager.c									\
					server/Database/factories/create_team.c						\
					server/Database/factories/create_user.c						\
					server/Database/factories/create_reply.c					\
					server/Database/factories/create_thread.c					\
					server/Database/factories/create_channel.c					\
					server/Database/factories/create_private_msg.c				\
					server/Database/getter/get_team.c							\
					server/Database/getter/get_user.c							\
					server/Database/getter/get_reply.c							\
					server/Database/getter/get_thread.c							\
					server/Database/getter/get_channel.c						\
					server/Database/getter/get_private_msg.c					\
					server/Database/updater/user_subscription_add.c				\
					server/Database/updater/user_subscription_remove.c			\
					server/Database/serializer/serializer_channel_t.c			\
					server/Database/serializer/serializer_private_msg_t.c		\
					server/Database/serializer/serializer_reply_t.c				\
					server/Database/serializer/serializer_team_t.c				\
					server/Database/serializer/serializer_thread_t.c			\
					server/Database/serializer/serializer_user_t.c				\
					server/Database/serializer/serializer_header_t.c			\
					server/Database/deserializer/deserializer_channel_t.c		\
					server/Database/deserializer/deserializer_private_msg_t.c	\
					server/Database/deserializer/deserializer_reply_t.c			\
					server/Database/deserializer/deserializer_team_t.c			\
					server/Database/deserializer/deserializer_thread_t.c		\
					server/Database/deserializer/deserializer_user_t.c			\
					server/Database/fill_data_length/fill_data_length.c			\

SRC_CLI	=	$(addprefix $(DSRC), $(SRC_FILES_CLI))
SRC_SRV	=	$(addprefix $(DSRC), $(SRC_FILES_SRV))

OBJ_CLI	=	$(SRC_CLI:.c=.o)
OBJ_SRV	=	$(SRC_SRV:.c=.o)

NAME_CLI	=	myteams_cli
NAME_SRV	=	myteams_server

INCLUDE = -I./include -I./libs/myteams -I./libs/socket/include
CFLAGS	+= -Wall -Wextra -W $(INCLUDE) #-Werror

LD_FLAGS += -lmysocket -L./libs/socket -lmyteams -L./libs/myteams -luuid

debug: CFLAGS += -g
debug: re

all:  client server

client: CFLAGS += -I./include/client
client: $(OBJ_CLI)
	@$(CC) -o $(NAME_CLI) $(OBJ_CLI) $(LD_FLAGS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME_CLI)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME_CLI)\n"$(DEFAULT)

server: CFLAGS += -I./include/server
server: $(OBJ_SRV)
	@$(CC) -o $(NAME_SRV) $(OBJ_SRV) $(LD_FLAGS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME_SRV)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME_SRV)\n"$(DEFAULT)

clean:
	$(RM) -f  $(OBJ_CLI) $(OBJ_SRV)
	@$(RM) -f *.gcda
	@$(RM) -f *.gcno

fclean:	clean
	$(RM) -f $(NAME_CLI) $(NAME_SRV)

re:	fclean all

#tests_run:
#	gcc -o $(NAME) $(SRC_UT) -I./include -lcriterion --coverage && ./$(NAME)

.PHONY :        clean fclean re

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LINE_RETURN	=	$(ECHO) ""
