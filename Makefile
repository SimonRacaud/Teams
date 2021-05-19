##
## EPITECH PROJECT, 2021
## Project_2021
## File description:
## Project makefile
##

DSRC	=	./src/

SRC_UT 			= 	tests/tests_project.c			\
					src/utility/signal_manager.c	\
					src/utility/strdup_format.c		\
					src/utility/walloc.c			\
					src/utility/strconcat.c			\
					src/utility/is_number.c			\
					src/network/request_create.c	\
					src/network/request_destroy.c	\
					src/network/request_parse.c		\
					src/network/request_write.c		\
					src/network/response_create.c	\
					src/network/response_destroy.c	\
					src/network/response_send.c	\
					src/network/response_read.c	\

SRC_FILES_CLI	=	client/main.c							\
					client/destroy/app_destroy.c			\
					client/init/app_init.c					\
					client/init/connect_to_server.c			\
					client/init/parse_args.c				\
					client/loop/app_loop.c					\
					client/loop/process_read.c				\
					client/loop/process_write.c				\
					client/loop/prompt.c					\
					client/logger/logger.c					\
					utility/is_ip.c							\
					utility/is_number.c						\
					utility/signal_manager.c				\
					utility/walloc.c						\
					utility/strdup_format.c					\
					utility/strconcat.c						\
					network/request_create.c				\
					network/request_destroy.c				\
					network/request_write.c					\
					network/response_destroy.c				\
					network/response_read.c					\
					network/response_send.c					\
					network/request_push.c					\
					network/debug_response.c				\

SRC_FILES_SRV	= 	server/main.c												\
					\
					utility/signal_manager.c									\
					utility/strdup_format.c										\
					utility/walloc.c											\
					utility/is_number.c											\
					utility/strconcat.c											\
					utility/walen.c												\
					utility/is_empty.c											\
					\
					server/app/app_create.c										\
					server/app/app_destroy.c									\
					server/app/app_loop.c										\
					server/app/app_select.c										\
					server/app/client.c											\
					server/app/process_request.c								\
					server/request/request_execute.c							\
					\
					network/request_create.c									\
					network/request_destroy.c									\
					network/request_parse.c										\
					network/request_write.c										\
					network/response_create.c									\
					network/response_destroy.c									\
					network/response_read.c										\
					network/response_send.c										\
					network/reply.c												\
					network/body/body_maker_team.c								\
					network/body/body_maker_channel.c							\
					network/body/body_maker_user.c								\
					network/body/body_maker_private_msg.c						\
					network/body/body_maker_reply.c								\
					network/body/body_maker_thread.c							\
					network/body/body_maker_string.c							\
					\
					server/handler/handler_help.c								\
					server/handler/handler_user.c								\
					server/handler/handler_send.c								\
					server/handler/handler_users.c								\
					server/handler/handler_login.c								\
					server/handler/handler_logout.c								\
					server/handler/handler_messages.c							\
					server/handler/handler_tools/handler_tools.c				\
					\
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
					server/Database/fill_data/fill_data_length.c				\
					server/Database/fill_data/run_fill_data.c					\
					server/Database/fill_data/get_nb_team_from_user.c			\
					server/Database/create_database_save_t.c					\

SRC_CLI	=	$(addprefix $(DSRC), $(SRC_FILES_CLI))
SRC_SRV	=	$(addprefix $(DSRC), $(SRC_FILES_SRV))

OBJ_CLI	=	$(SRC_CLI:.c=.o)
OBJ_SRV	=	$(SRC_SRV:.c=.o)

NAME_CLI	=	myteams_cli
NAME_SRV	=	myteams_server
NAME_UT 	=	test.out
NAME_LIB_TEAMS = libmyteams.so

INCLUDE = -I./include -I./libs/myteams -I./libs/socket/include -I./libs/
CFLAGS	+= -Wall -Wextra -W $(INCLUDE) #-Werror

LD_FLAGS += -lmysocket -L./libs/socket -lmyteams -L./libs/myteams -luuid -lm

all:  client server

client: CFLAGS += -I./include/client
client: socket $(OBJ_CLI)
	@$(CC) -o $(NAME_CLI) $(OBJ_CLI) $(LD_FLAGS) -Wl,-rpath=$(PWD) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME_CLI)\n"$(DEFAULT) || \
		($(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME_CLI)\n"$(DEFAULT) && exit 1)

server: CFLAGS += -I./include/server
server: socket $(OBJ_SRV)
	@$(CC) -o $(NAME_SRV) $(OBJ_SRV) $(LD_FLAGS) -Wl,-rpath=$(PWD) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME_SRV)\n"$(DEFAULT) || \
		($(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME_SRV)\n"$(DEFAULT) && exit 1)

socket:
	@make -C libs/socket
	@ln -sf ./libs/myteams/$(NAME_LIB_TEAMS) $(NAME_LIB_TEAMS)

clean:
	make clean -C libs/socket
	@$(RM) -f  $(OBJ_CLI) $(OBJ_SRV)
	@$(RM) -f *.gcda
	@$(RM) -f *.gcno

fclean:	clean
	$(RM) -f $(NAME_CLI) $(NAME_SRV) $(NAME_UT)
	$(RM) -f $(NAME_LIB_TEAMS)

re:	fclean all

tests_run: socket
	gcc -o $(NAME_UT) $(SRC_UT) $(INCLUDE) $(LD_FLAGS) -Wl,-rpath=$(PWD) -lcriterion --coverage && ./$(NAME_UT)

coverage: tests_run
	@gcovr -r . --exclude-directories tests
	@gcovr -b --exclude-directories tests

debug: CFLAGS += -g
debug: re
	@make debug -C libs/socket

debugall: CFLAGS += -g
debugall: all

.PHONY:	client server clean socket fclean re tests_run coverage debug

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
